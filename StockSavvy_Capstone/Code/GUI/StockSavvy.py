from tkinter import *
from customtkinter import *
from matplotlib.figure import Figure 
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg, NavigationToolbar2Tk)
from customtkinter import CTkButton as Button
from customtkinter import CTkFrame as Frame
from customtkinter import CTkLabel as Label
from customtkinter import CTkEntry as Entry
from customtkinter import CTkOptionMenu as Menu
from customtkinter import CTkRadioButton as Radiobutton
from helper_funtions import HelperFunctions
from data_modification import DataModification
import os



class StockSavvyGui(HelperFunctions, DataModification):
    def __init__(self, parent):
        self.parent = parent
        self.current_directory = os.path.join(os.getcwd(), "Desktop/StockSavvy/_internal")
        HelperFunctions(self.parent)
        DataModification()

        self.frames = {
            "sidebar": Frame,  
            "activity": Frame,
            "main": Frame,
            "signup": Frame,
            "stock": Frame,
            "forgot": Frame,
            "prediction": Frame
        }
        self.labels = {
            "title": Label,
            "info": Label,
            "appearance": Label,
            "theme": Label,
            "username": Label,
            "password": Label,
            "re_password": Label,
            "signup": Label,
            "pcharacters": Label,
            "stock": Label,
            "stock_option": Label,
            "stock_name": Label,
            "last_update": Label,
            "graph": Label,
            "stock_headings": [],
            "stock_values": []
        }
        self.buttons = {
            "set_appearance": Button,
            "set_theme": Button,
            "forgot_password": Button,
            "verify": Button,
            "show_password": Button,
            "change_password": Button,
            "signup": Button,
            "back": Button,
            "create_user": Button,
            "predict": Button,
            "stocks": [],
            "stock_page": Button,
            "home_page": Button,
            "low": Radiobutton,
            "high": Radiobutton,
            "close": Radiobutton
        }
        self.textvariables = {
            "username": StringVar(),
            "password": StringVar(),
            "re_password": StringVar(),
            "user_option": StringVar(),
            "graph": StringVar()
        }
        self.entry = {
            "username": Entry,
            "password": Entry,
            "re_password": Entry
        }
        self.OptionMenu = {
            "change_appearance": Menu,
            "change_theme": Menu
        }

        #Graph data
        self.data=''

        #Graph Figure
        self.figure = Figure()

        #Selection by user
        self.user_selection = "none"

        #Stock list
        self.stocks = ["Apple", "Tesla", "Amazon", "Pepsi Co", "Google", "Microsoft"]
        
        #list of tuples
        self.authentication = [("user", "password")]

        #Creating basic frame on the window
        set_appearance_mode("System")

        #Sidebar
        self.create_sidebar()

        #row and column config of sidebar
        self.frames["sidebar"].rowconfigure(0, weight=1)
        self.frames["sidebar"].rowconfigure(1, weight=1)
        self.frames["sidebar"].rowconfigure(2, weight=1)
        self.frames["sidebar"].rowconfigure(3, weight=0)
        self.frames["sidebar"].rowconfigure(4, weight=1)
        self.frames["sidebar"].rowconfigure(5, weight=1)        
        self.frames["sidebar"].columnconfigure(0, weight=1)

        #adding activity frame
        # self.frames["activity"] = Frame(self.parent, corner_radius=0,bg_color="blue")
        # self.frames["activity"].grid(row=0, column=1, sticky="NSEW")

        #row and column config of window
        self.parent.rowconfigure(0, weight=1)
        self.parent.columnconfigure(0, weight=1)
        self.parent.columnconfigure(1, weight=10)

        #Main page call
        self.main_page()
    
    def create_sidebar(self):
        self.frames["sidebar"] = Frame(self.parent, corner_radius=0)
        self.frames["sidebar"].grid(row=0, column=0, sticky="NSEW")
        
        self.labels["title"] = Label(self.frames["sidebar"], text="StockSavvy", font=CTkFont(size=40, weight="bold"))
        self.labels["title"].grid(row=0, column=0, sticky="N")

        self.labels["info"] = Label(self.frames["sidebar"], 
                                    text="Welcome to the Graphical User Interface for StockSavvy.\n\n" 
                                          "This is an intuitive interface to analyze stocks. Users can select a stock and view key metrics such as its 52-week high, 52-week low, 50-day moving average, 100-day moving average, and 200-day moving average.\n\n"
                                          "The GUI displays the predicted closing price of the selected stock, along with a graph comparing the expected price with the actual price.\n ",
                                    font=CTkFont(size=16), wraplength=250, justify="center")
        self.labels["info"].grid(row=1, column=0, sticky=N, padx=5, pady=5)

        self.labels["appearance"] = Label(self.frames["sidebar"], text="Switch Mode:")
        self.labels["appearance"].grid(row=2, column=0, sticky="S")

        self.OptionMenu["change_appearance"] = Menu(self.frames["sidebar"], values=["System", "Dark", "Light"], command=self.change_appearance)
        self.OptionMenu["change_appearance"].grid(row=3, column=0, sticky="N")

        self.labels["theme"] = Label(self.frames["sidebar"], text="Switch Theme:")
        self.labels["theme"].grid(row=4, column=0, sticky="S")

        self.OptionMenu["theme"] = Menu(self.frames["sidebar"], values=["green", "blue", "dark-blue"], command=self.change)
        self.OptionMenu["theme"].grid(row=5, column=0, sticky="N")

    def change(self):
        self.parent.destroy
        p = self.parent
        self.__init__(p)
    
    def main_page(self):
        self.clear()
        self.frames["main"] = Frame(self.parent, corner_radius=0, fg_color="transparent")
        self.frames["main"].grid(row=0, column=1)
        self.frames["main"].tkraise()

        #Clear TextVariables
        self.textvariables["username"].set("")
        self.textvariables["password"].set("")
        
        Login = Label(self.frames["main"], text="Login", font=CTkFont(size=25, weight="bold"))
        Login.grid(row=0, column=0, sticky=W)

        #Username
        self.labels["username"] = Label(self.frames["main"], text="Enter your username:")
        self.labels["username"].grid(row=1, column=0, sticky=W)
        self.entry["username"] = Entry(self.frames["main"], textvariable=self.textvariables["username"])
        self.entry["username"].grid(row=1, column=1, sticky=NSEW)

        #Password
        self.labels["password"] = Label(self.frames["main"], text="Enter your password:")
        self.labels["password"].grid(row=2, column=0, sticky=W)
        self.entry["password"] = Entry(self.frames["main"], textvariable=self.textvariables["password"], show="*")
        self.entry["password"].grid(row=2, column=1, sticky=NSEW)
        
        #Buttons
        self.buttons["show_password"] = Button(self.frames["main"], text="Show Password", command=lambda page="main":self.toggle_password(page))
        self.buttons["show_password"].grid(row=2, column=2, sticky=NSEW, padx=10)
        self.buttons["forgot_password"] = Button(self.frames["main"], text="Forgot Password",command=self.forgot_page)
        self.buttons["forgot_password"].grid(row=3, column=0, padx=10, pady=10, sticky=NSEW)
        self.buttons["verify"] = Button(self.frames["main"], text="Verify", command=self.check_credentials)
        self.buttons["verify"].grid(row=3, column=1, padx=10, pady=10, sticky=NSEW)
        self.buttons["signup"] = Button(self.frames["main"], text="Sign Up", command=self.signup_page)
        self.buttons["signup"].grid(row=4, column=1, padx=10, pady=10, sticky=NSEW)

        #Signup page label
        self.labels["signup"] = Label(self.frames["main"], text="If you do not have an account: ")
        self.labels["signup"].grid(row=4,column=0, sticky=W)

    def signup_page(self):
        self.clear()
        self.frames["signup"] = Frame(self.parent, corner_radius=0, fg_color="transparent")
        self.frames["signup"].grid(row=0, column=1)
        self.frames["signup"].tkraise()

        #Heading
        Signup = Label(self.frames["signup"], text="User Registeration", font=CTkFont(size=25, weight="bold"))
        Signup.grid(row=0, column=0, sticky="W")
        
        #Clear TextVariables
        self.textvariables["username"].set("")
        self.textvariables["password"].set("")
        self.textvariables["re_password"].set("")
        
        #Username
        self.labels["username"] = Label(self.frames["signup"], text="Enter your username:")
        self.labels["username"].grid(row=1, column=0, sticky=W)
        self.entry["username"] = Entry(self.frames["signup"], textvariable=self.textvariables["username"])
        self.entry["username"].grid(row=1, column=1, sticky=NSEW)
        
        #Password
        self.labels["password"] = Label(self.frames["signup"], text="Enter your password:")
        self.labels["password"].grid(row=2, column=0, sticky=W)
        self.entry["password"] = Entry(self.frames["signup"], textvariable=self.textvariables["password"], show="*")
        self.entry["password"].grid(row=2, column=1, sticky=NSEW)

        #Re_Password
        self.labels["re_password"] = Label(self.frames["signup"], text="Re-enter your password:")
        self.labels["re_password"].grid(row=3, column=0, sticky=W)
        self.entry["re_password"] = Entry(self.frames["signup"], textvariable=self.textvariables["re_password"], show="*")
        self.entry["re_password"].grid(row=3, column=1, sticky=NSEW)
        
        #Buttons
        self.buttons["show_password"] = Button(self.frames["signup"], text="Show Password", command=lambda page="signup":self.toggle_password(page))
        self.buttons["show_password"].grid(row=3, column=2, sticky=NSEW, padx=10)
        self.buttons["back"] = Button(self.frames["signup"], text="Back", command=self.main_page)
        self.buttons["back"].grid(row=4, column=0, padx=10, pady=10, sticky=NSEW)
        self.buttons["create_user"] = Button(self.frames["signup"], text="Create User", command=self.create_user)
        self.buttons["create_user"].grid(row=4, column=1, padx=10, pady=10, sticky=NSEW)

        #Password Label
        self.labels["pcharacters"] = Label(self.frames["signup"], text="8 to 16 characters")
        self.labels["pcharacters"].grid(row=2, column=2, sticky=W, padx=10)

    def forgot_page(self):
        self.clear()
        self.frames["forgot"] = Frame(self.parent, corner_radius=0, fg_color="transparent")
        self.frames["forgot"].grid(row=0, column=1)
        self.frames["forgot"].tkraise()

        #Heading 
        forgot = Label(self.frames["forgot"], text="Reset Password", font=CTkFont(size=25, weight="bold"))
        forgot.grid(row=0, column=0, sticky=W)
        
        #Clear TextVariables
        self.textvariables["username"].set("")
        self.textvariables["password"].set("")
        self.textvariables["re_password"].set("")
        
        #Username
        self.labels["username"] = Label(self.frames["forgot"], text="Enter your username:")
        self.labels["username"].grid(row=1, column=0, sticky=W)
        self.entry["username"] = Entry(self.frames["forgot"], textvariable=self.textvariables["username"])
        self.entry["username"].grid(row=1, column=1, sticky=NSEW)
        
        #Password
        self.labels["password"] = Label(self.frames["forgot"], text="Enter your new password:")
        self.labels["password"].grid(row=2, column=0, sticky=W)
        self.entry["password"] = Entry(self.frames["forgot"], textvariable=self.textvariables["password"], show="*")
        self.entry["password"].grid(row=2, column=1, sticky=NSEW)

        #Re_Password
        self.labels["re_password"] = Label(self.frames["forgot"], text="Re-enter your new password:")
        self.labels["re_password"].grid(row=3, column=0, sticky=W)
        self.entry["re_password"] = Entry(self.frames["forgot"], textvariable=self.textvariables["re_password"], show="*")
        self.entry["re_password"].grid(row=3, column=1, sticky=NSEW)
        
        #Buttons
        self.buttons["show_password"] = Button(self.frames["forgot"], text="Show Password", command=lambda page="forgot":self.toggle_password(page))
        self.buttons["show_password"].grid(row=3, column=2, sticky=NSEW, padx=10)
        self.buttons["back"] = Button(self.frames["forgot"], text="Back", command=self.main_page)
        self.buttons["back"].grid(row=4, column=0, padx=10, pady=10, sticky=NSEW)
        self.buttons["change_password"] = Button(self.frames["forgot"], text="Change Password", command=self.change_password)
        self.buttons["change_password"].grid(row=4, column=1, padx=10, pady=10, sticky=NSEW)

        #Password Label
        self.labels["pcharacters"] = Label(self.frames["forgot"], text="8 to 16 characters")
        self.labels["pcharacters"].grid(row=2, column=2, sticky=W, padx=10)
    
    def stock_page(self):
        self.clear()
        self.frames["stock"] = Frame(self.parent, corner_radius=0, fg_color="transparent")
        self.frames["stock"].grid(row=0, column=1)
        self.frames["stock"].tkraise()
        
        #Heading 
        stock = Label(self.frames["stock"], text="Stocks", font=CTkFont(size=25, weight="bold"))
        stock.grid(row=0, column=0, padx=10, pady=10, sticky=W)
        #Lable for stocks
        self.labels["stock"] = Label(self.frames["stock"], text="Stocks:", font=CTkFont(size=25, weight="bold"))
        self.labels["stock"].grid(row=0, column=0, padx=10, pady=10, sticky=W)

        #Creating Radio Button list
        i = 1
        for stock in self.stocks:
            button = Radiobutton(self.frames["stock"], text=stock, variable=self.textvariables["user_option"], value=stock, command=self.option_selected)
            button.grid(row=i, column=0, padx=10, pady=10, sticky=W)
            self.buttons["stocks"].append(button)
            i += 1
        
        #Initial Button to go back to login page
        self.buttons["back"] = Button(self.frames["stock"], text="Back", command=self.main_page)
        self.buttons["back"].grid(row=i, column=0, padx=10, pady=10, sticky=W)

        #Label to show option 
        self.labels["stock_option"] = Label(self.frames["stock"], text="")
        self.labels["stock_option"].grid(row=i, column=1, padx=10, pady=10, sticky=W)

        #Prediction Button
        self.buttons["predict"] = Button(self.frames["stock"], text="Predict", state=DISABLED, command=self.prediction_page)
        self.buttons["predict"].grid(row=i, column=2, padx=10, pady=10, sticky=W)
    
    def prediction_page(self):
        self.clear()
        self.frames["prediction"] = Frame(self.parent, corner_radius=0, fg_color="transparent")
        self.frames["prediction"].grid(row=0, column=1, sticky=NSEW)
        self.frames["prediction"].tkraise()

        today = self.day()

        Headings = ["52 Week High", "52 Week Low", "200 Days Avg", "100 Days Avg", "50 Days Avg", f"{today} Closing Price"]
        Values = self.weeklyUpdate(self.user_selection)
        LastUpdate = Values.pop(len(Values)-1)
        ClosingPrice = self.ClosingValue(self.user_selection)
        Values.append(ClosingPrice)

        #Stock label
        self.labels["stock_name"] = Label(self.frames["prediction"], text=self.user_selection)
        self.labels["stock_name"].grid(row=0, column=0, sticky=NSEW, columnspan=3)
        self.labels["stock_name"].configure(font=('Helvetica bold', 40))

        #Last Updated Label
        self.labels["last_update"] = Label(self.frames["prediction"], text=f"Last Updated: {LastUpdate}")
        self.labels["last_update"].grid(row=0, column=4, padx=10, pady=10, sticky=SE)

        self.labels["graph"] = Label(self.frames["prediction"], text="Please choose from the following options:")
        self.labels["graph"].grid(row=2, column=0, padx=10, pady=1, sticky=W)

        #Creating Radio Buttons for graph modification
        self.buttons['low'] = Radiobutton(self.frames["prediction"], text="Low", variable=self.textvariables["graph"], value=os.path.join(self.current_directory ,f"Data/{self.user_selection}/Stock_ML_Low.csv"), command=self.ModifyGraph)
        self.buttons['low'].grid(row=3, column=0, padx=10, pady=1, sticky=NSEW, rowspan=1)
        self.buttons['high'] = Radiobutton(self.frames["prediction"], text="High", variable=self.textvariables["graph"], value=os.path.join(self.current_directory ,f"Data/{self.user_selection}/Stock_ML_High.csv"), command=self.ModifyGraph)
        self.buttons['high'].grid(row=4, column=0, padx=10, pady=1, sticky=NSEW, rowspan=1)
        self.buttons['close'] = Radiobutton(self.frames["prediction"], text="Close", variable=self.textvariables["graph"], value=os.path.join(self.current_directory ,f"Data/{self.user_selection}/Stock_ML_CLOSE.csv"), command=self.ModifyGraph)
        self.buttons['close'].grid(row=5, column=0, padx=10, pady=1, sticky=NSEW, rowspan=1)


        #Creating Data Heading
        i = 3
        for head in Headings:
            h = Label(self.frames["prediction"], text=head + ": ")
            h.grid(row=i, column=3, sticky=SW)
            h.configure(font=('Helvetica bold', 20))
            i += 1
            self.labels["stock_headings"].append(h)
        
        #Creating Data Values
        j = 3
        for val in Values:
            v = Label(self.frames["prediction"], text=round(val,2))
            v.grid(row=j, column=4, sticky=SW)
            v.configure(font=('Helvetica bold', 20))
            j += 1
            self.labels["stock_values"].append(v)
        
        #Creating stock page button
        self.buttons["stock_page"] = Button(self.frames["prediction"], text="Back", command=self.stock_page)
        self.buttons["stock_page"].grid(row=i, column=3, sticky=W)

        #Creating home page button
        self.buttons["home_page"] = Button(self.frames["prediction"], text="Logout", command=self.main_page)
        self.buttons["home_page"].grid(row=j, column=4, sticky=W)
        
        self.frames["prediction"].rowconfigure(0, weight=1)
        self.frames["prediction"].rowconfigure(1, weight=1)
        self.frames["prediction"].rowconfigure(2, weight=1)
        self.frames["prediction"].rowconfigure(3, weight=1)
        self.frames["prediction"].rowconfigure(4, weight=1)
        self.frames["prediction"].rowconfigure(5, weight=1)
        self.frames["prediction"].rowconfigure(6, weight=1)
        self.frames["prediction"].rowconfigure(7, weight=1)
        self.frames["prediction"].rowconfigure(8, weight=1)
        self.frames["prediction"].rowconfigure(9, weight=1)

        self.frames["prediction"].columnconfigure(0, weight=1)
        self.frames["prediction"].columnconfigure(1, weight=1)
        self.frames["prediction"].columnconfigure(2, weight=1)
        self.frames["prediction"].columnconfigure(3, weight=1)
        self.frames["prediction"].columnconfigure(4, weight=1)
        self.frames["prediction"].columnconfigure(5, weight=1)

    def change_theme(self, theme):
        if theme == "green":
            set_default_color_theme("green")
        if theme == "dark-blue":
            set_default_color_theme("dark-blue")
        else:
            set_default_color_theme("blue")

if __name__ == '__main__':
    window = CTk()
    window.geometry(str(window.winfo_screenwidth()) + "x" + str(window.winfo_screenheight()))
    window.title("StockSavvy GUI")
    main_window = StockSavvyGui(window)
    window.mainloop()