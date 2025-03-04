from tkinter import *
from matplotlib.figure import Figure 
from customtkinter import *
import matplotlib.dates as mdates
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg, NavigationToolbar2Tk)
from datetime import date

class HelperFunctions:
    def __init__(self, parent):
        self.parent = parent

    def plot(self): 
        self.labels["graph"].grid_forget()
        self.buttons['low'].grid(row=2, column=0, padx=10, pady=1, sticky=NSEW, rowspan=1)
        self.buttons['high'].grid(row=2, column=1, padx=10, pady=1, sticky=NSEW, rowspan=1)
        self.buttons['close'].grid(row=2, column=2, padx=10, pady=1, sticky=NSEW, rowspan=1)
        self.figure = Figure(figsize=(7, 7))
        ax = self.figure.add_subplot(111)

        # Plotting the data
        ax.plot(self.data.index, self.data['Expected'], label='Expected', color='blue')
        ax.plot(self.data.index, self.data['Actual'], label='Actual', color='red')

        # Formatting the date axis
        ax.xaxis.set_major_formatter(mdates.DateFormatter('%Y-%m'))
        ax.xaxis.set_major_locator(mdates.MonthLocator(interval=3))
        self.figure.autofmt_xdate()

        # Adding labels and title
        ax.set_xlabel('Date (Quarterly)')
        ax.set_ylabel('Price ($)')
        ax.set_title('Expected Price vs Actual Price')
        ax.legend()
        ax.grid(True)

        canvas = FigureCanvasTkAgg(self.figure, master = self.frames["prediction"])   
        canvas.draw() 
    
        # placing the canvas on the Tkinter window 
        canvas.get_tk_widget().grid(row=3, column=0, padx=10, sticky=W, columnspan=3, rowspan=7)

    
    def option_selected(self):
        self.user_selection = str(self.textvariables["user_option"].get())
        label = f'Click "Predict" to predict the stock price of {self.user_selection} '
        self.labels["stock_option"].configure(text=label)
        self.buttons["predict"].configure(state = ACTIVE)
    
    def toggle_password(self, page):
        if page == "main":
            if self.entry["password"].cget('show') == "*":
                self.entry["password"].configure(show = '')
                self.buttons["show_password"].configure(text="Hide Password")
            else:
                self.entry["password"].configure(show = "*")
                self.buttons["show_password"].configure(text="Show Password")
        else:
            if self.entry["password"].cget('show') == "*":
                self.entry["password"].configure(show = '')
                self.entry["re_password"].configure(show = '' )
                self.buttons["show_password"].configure(text="Hide Password")
            else:
                self.entry["password"].configure(show = "*")
                self.entry["re_password"].configure(show = "*" )
                self.buttons["show_password"].configure(text="Show Password")
    
    def clear(self):
        i = 1
        for widgets in self.parent.winfo_children():
            if i != 1:
                widgets.grid_forget()
            i += 1
    
    def change_appearance(self, appearance):
        set_appearance_mode(appearance)
    
    def change_theme(self, theme):
        set_default_color_theme(theme)

    def day(self):
        days=["Monday's", "Tuesday's", "Wednesday's", "Thursday's", "Friday's"]
        today = date.today().weekday()
        
        if today+1 == 5 or today+1 == 6:
            return days[4]
        elif today+1 == 7:
            return days[0]
        else:
            return days[today+1]
        