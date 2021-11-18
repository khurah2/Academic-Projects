from django.http import HttpResponse,HttpResponseNotFound
from django.shortcuts import render,redirect,get_object_or_404
from django.contrib.auth.forms import AuthenticationForm, UserCreationForm, PasswordChangeForm
from django.contrib.auth import authenticate, login, logout, update_session_auth_hash
from django.contrib import messages
from django.contrib.auth.models import User
from . import models

def messages_view(request):
    """Private Page Only an Authorized User Can View, renders messages page
       Displays all posts and friends, also allows user to make new posts and like posts
    Parameters
    ---------
      request: (HttpRequest) - should contain an authorized user
    Returns
    --------
      out: (HttpResponse) - if user is authenticated, will render private.djhtml
    """
    if request.user.is_authenticated:
        user_info = models.UserInfo.objects.get(user=request.user)


        # TODO Objective 9: query for posts (HINT only return posts needed to be displayed)
        posts = list(models.Post.objects.all().order_by('-id').values('id','owner_id','content','timestamp'))
        new_post=[]
        
        for post in posts:
            user=User.objects.get(id=post['owner_id'])
            post['user']=user
            post_likes=models.Post.objects.get(id=post['id']).likes.all()
            post['likes_count']=len(post_likes)
            post['timestamp']=post['timestamp'].strftime("%B %d,%Y %I:%M %p")
            liked=[]
            for i in post_likes.values():
                liked.append(i['user_id'])
            if request.user.id in liked:
                post['like_disabled']=True
            else:
                post['like_disabled']=False
            new_post.append(post)

        # TODO Objective 10: check if user has like post, attach as a new attribute to each post

        context = { 'user_info' : user_info,
                    'posts' : new_post }
        request.session['counter_ppl']=1

        return render(request,'messages.djhtml',context)

    request.session['failed'] = True
    return redirect('login:login_view')

def account_view(request):
    """Private Page Only an Authorized User Can View, allows user to update
       their account information (i.e UserInfo fields), including changing
       their password
    Parameters
    ---------
      request: (HttpRequest) should be either a GET or POST
    Returns
    --------
      out: (HttpResponse)
                 GET - if user is authenticated, will render account.djhtml
                 POST - handle form submissions for changing password, or User Info
                        (if handled in this view)
    """
    # TODO Objective 3: Create Forms and Handle POST to Update UserInfo / Password
    if not request.user.is_authenticated:
        redirect('login:login_view')
    if request.method == 'POST':
        form = PasswordChangeForm(request.user, request.POST)
        update_form = models.UserUpdateForm(request.POST)
        if form.is_valid():
            user = form.save()
            update_session_auth_hash(request, user)
        if update_form.is_valid():
            user_info = models.UserInfo.objects.get(user=request.user)
            user_info.employment=request.POST['employment']
            user_info.location=request.POST['location']
            user_info.birthday=request.POST['birthday']
            try:
                userinterest=models.Interest.objects.get_or_create(label=request.POST['interest'])
            except:  
                print('')   
            user_info.interests.add(userinterest[0])
            user_info.save()
        return redirect('social:messages_view')
    else:
        form = PasswordChangeForm(request.user)
        user_info = models.UserInfo.objects.get(user=request.user)
        update_form = models.UserUpdateForm(instance=user_info)
        context = { 'user_info' : user_info,
                'form' : form,
                'update_form' : update_form}
        return render(request, 'account.djhtml' , context)
 
def people_view(request):
    """Private Page Only an Authorized User Can View, renders people page
       Displays all users who are not friends of the current user and friend requests
    Parameters
    ---------
      request: (HttpRequest) - should contain an authorized user
    Returns
    --------
      out: (HttpResponse) - if user is authenticated, will render people.djhtml
    """
    if request.user.is_authenticated:
        user_info = models.UserInfo.objects.get(user=request.user)
        # TODO Objective 4: create a list of all users who aren't friends to the current user (and limit size)
        frnd_list = list(user_info.friends.all().values())
        ppl_list = list(models.UserInfo.objects.all().values())
        sent_request=list(models.FriendRequest.objects.filter(from_user=user_info).values('to_user_id'))
        sent_request_user=[]
        for i in sent_request:
            sent_request_user.append(i['to_user_id'])

        all_people=[]
        for user in ppl_list:
            if user not in frnd_list:
                user['user']=User.objects.get(id=user['user_id'])
                if user['user'] != request.user:

                    if user['user_id'] in sent_request_user:
                        user['request_sent']=True
                    else:
                        user['request_sent']=False

                    all_people.append(user)

        # TODO Objective 5: create a list of all friend requests to current user
        
        frnd_request = list(models.FriendRequest.objects.filter(to_user=user_info).values())
        friend_requests=[]
        for frnd in frnd_request:
            user_info=models.UserInfo.objects.get(user_id=frnd['from_user_id'])
            user_info=user_info.__dict__
            user_info['user']=User.objects.get(id=user_info['user_id'])
            friend_requests.append(user_info)


        context = { 'user_info' : user_info,
                    'friend_requests' : friend_requests,
                    'all_people':  all_people}

        return render(request,'people.djhtml',context)

    request.session['failed'] = True
    return redirect('login:login_view')

def like_view(request):
    '''Handles POST Request recieved from clicking Like button in messages.djhtml,
       sent by messages.js, by updating the corrresponding entry in the Post Model
       by adding user to its likes field
    Parameters
	----------
	  request : (HttpRequest) - should contain json data with attribute postID,
                                a string of format post-n where n is an id in the
                                Post model

	Returns
	-------
   	  out : (HttpResponse) - queries the Post model for the corresponding postID, and
                             adds the current user to the likes attribute, then returns
                             an empty HttpResponse, 404 if any error occurs
    '''
    post_id = request.POST.get('post_id')
    if post_id is not None:
        # remove 'post-' from postID and convert to int
        # TODO Objective 10: parse post id from postIDReq
        
        if request.user.is_authenticated:
            # TODO Objective 10: update Post model entry to add user to likes field
            post=models.Post.objects.get(id=post_id)
            user_info=models.UserInfo.objects.get(user_id=request.user.id)
            post.likes.add(user_info)
            post.save()
            status = {'status':'success'}
            return HttpResponse(status,200) 
        else:
            return redirect('login:login_view')

    return HttpResponseNotFound('like_view called without postID in POST')

def post_submit_view(request):
    '''Handles POST Request recieved from submitting a post in messages.djhtml by adding an entry
       to the Post Model
    Parameters
	----------
	  request : (HttpRequest) - should contain json data with attribute postContent, a string of content

	Returns
	-------
   	  out : (HttpResponse) - after adding a new entry to the POST model, returns an empty HttpResponse,
                             or 404 if any error occurs
    '''
    postContent = request.POST.get('content')
    if postContent is not None:
        if request.user.is_authenticated:

            # TODO Objective 8: Add a new entry to the Post model
            user_info=models.UserInfo.objects.get(user_id=request.user.id)
            user_post=models.Post(owner=user_info,content=postContent)
            user_post.save()
            status = {'status':'success'}
            # return status='success'
            return HttpResponse(status,200)
        else:
            return redirect('login:login_view')

    return HttpResponseNotFound('post_submit_view called without postContent in POST')

def more_post_view(request):
    '''Handles POST Request requesting to increase the amount of Post's displayed in messages.djhtml
    Parameters
	----------
	  request : (HttpRequest) - should be an empty POST

	Returns
	-------
   	  out : (HttpResponse) - should return an empty HttpResponse after updating hte num_posts sessions variable
    '''
    if request.user.is_authenticated:
        # update the # of posts dispalyed

        # TODO Objective 9: update how many posts are displayed/returned by messages_view
        i = request.session['counter_posts']
        request.session['counter_posts'] = i+1
        status = {'status':'success'}
        return HttpResponse(status,200) 

    return redirect('login:login_view')

def more_ppl_view(request):
    '''Handles POST Request requesting to increase the amount of People displayed in people.djhtml
    Parameters
	----------
	  request : (HttpRequest) - should be an empty POST

	Returns
	-------
   	  out : (HttpResponse) - should return an empty HttpResponse after updating the num ppl sessions variable
    '''
    if request.user.is_authenticated:
        # update the # of people dispalyed

        # TODO Objective 4: increment session variable for keeping track of num ppl displayed

        # return status='success'
        i = request.session['counter_ppl']
        request.session['counter_ppl'] = i+1
        status = {'status':'success'}
        return HttpResponse(status,200)  

    return redirect('login:login_view')

def friend_request_view(request):
    '''Handles POST Request recieved from clicking Friend Request button in people.djhtml,
       sent by people.js, by adding an entry to the FriendRequest Model
    Parameters
	----------
	  request : (HttpRequest) - should contain json data with attribute frID,
                                a string of format fr-name where name is a valid username

	Returns
	-------
   	  out : (HttpResponse) - adds an etnry to the FriendRequest Model, then returns
                             an empty HttpResponse, 404 if POST data doesn't contain frID
    '''
    frID = request.POST.get('frID')
    if frID is not None:
        # remove 'fr-' from frID
        username = frID

        if request.user.is_authenticated:
            # TODO Objective 5: add new entry to FriendRequest
            obj1=models.UserInfo.objects.get(user_id=username)
            obj2=models.UserInfo.objects.get(user=request.user)
            var=models.FriendRequest.objects.get_or_create(to_user = obj1, from_user = obj2)
            
            # return status='success'
            status = {'status':'success'}
            return HttpResponse(status,200)
        else:
            return redirect('login:login_view')

    return HttpResponseNotFound('friend_request_view called without frID in POST')

def accept_decline_view(request):
    '''Handles POST Request recieved from accepting or declining a friend request in people.djhtml,
       sent by people.js, deletes corresponding FriendRequest entry and adds to users friends relation
       if accepted
    Parameters
	----------
	  request : (HttpRequest) - should contain json data with attribute decision,
                                a string of format A-name or D-name where name is
                                a valid username (the user who sent the request)

	Returns
	-------
   	  out : (HttpResponse) - deletes entry to FriendRequest table, appends friends in UserInfo Models,
                             then returns an empty HttpResponse, 404 if POST data doesn't contain decision
    '''
    data = request.POST.get('decision')
    user_id=request.POST.get('user_id')
    if data is not None:
        # TODO Objective 6: parse decision from data

        if request.user.is_authenticated:

            # TODO Objective 6: delete FriendRequest entry and update friends in both Users
            obj1=models.UserInfo.objects.get(user_id=request.user.id)
            obj2=models.UserInfo.objects.get(user_id=user_id)
            var=models.FriendRequest.objects.get(to_user=obj1,from_user=obj2)
            if(data=='A'):
                obj1.friends.add(obj2)
                var.delete()
            else:
                var.delete()


            status = {'status':'success'}
            # return status='success'
            return HttpResponse(status,200)
        else:
            return redirect('login:login_view')

    return HttpResponseNotFound('accept-decline-view called without decision in POST')

