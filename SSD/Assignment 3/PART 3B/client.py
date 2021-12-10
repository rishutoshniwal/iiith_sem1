import requests
import json
import random

def printMenu():
    print("\n\n\n")
    print("1. To register a user")
    print("2. login a user")
    print("3. logout user")
    print("4. show current menu")
    print("5. Order and get current bill")
    print("6. get previous bill numbers and print selected choice bill")
    print("7. Add item to the menu (by chef only)")
    print("Any other number to quit \n\n\n\n")

def getOrders():
    y=[]
    while(True):
        moreOrder=int(input("Enter 1 to add more orders or any other digit otherwise  : "))
        if moreOrder!=1 :
            break
        x=[]
        item_id=int(input("Enter the item Id you want to order : "))
        plate_type=int(input("Enter 1 for half Plate or 2 for full plate : "))  
        quantity=int(input("Enter the quantity : "))  
        x.append(item_id)
        x.append(plate_type)
        x.append(quantity)
        # print(x)
        y.append(x)
       
    return y    
    

i=0
loggedin=False
loggedinUserName=''
chefLogin=False
while i<=10 :
    printMenu()
    cho=int(input("Enter your choice : "))
    if (cho == 1):
        if loggedin==True:
            print("You can register when current user will logout")
        else:
            username = input("Enter username: ")
            pass1 = input("Enter password: ")
            type = input("Enter usertpye: ")
            data = {
            "username" : username,
            "pass1" : pass1,
            "type" : type
               }
            response = requests.post(url='http://127.0.0.1:5000/register',json=data).content
            print(response.decode('ascii'))

    elif (cho == 2):
        username = input("Enter username: ")
        pass1 = input("Enter password: ")
        data = {
            "username" : username,
            "pass1" : pass1,
        }
        # resp=requests.post(url='http://127.0.0.1:5000/user',json=data).content
        response = requests.post(url='http://127.0.0.1:5000/login',json=data).content

        if loggedin==True and loggedinUserName==username:
            print("You are already logged in")
            continue

        if loggedin==True and loggedinUserName!=username:
            print("Someone else logged in")
            continue

        
        print(response.decode('ascii'))
        if(response.decode('ascii')== "Customer , Successfully Logged in"):
            loggedin=True
            loggedinUserName=username
        if(response.decode('ascii')== "Chef , Successfully Logged in"):
            loggedin=True
            loggedinUserName=username    
            chefLogin=True
    
    elif (cho == 3):
        if loggedin==True:
            data={}
            response = requests.post(url='http://127.0.0.1:5000/logout',json=data).content
            print(response.decode('ascii'))
            loggedin=False
            chefLogin=False
        else:
            print("Already logged out")    
    
    elif (cho == 4):
        data={}
        if loggedin==True:
            response = requests.post(url='http://127.0.0.1:5000/show_menu',json=data).content
            print(response.decode('ascii'))
        else:
            print("You need to login first")

    elif (cho == 5):

         if loggedin==True:
            data = {
            "username" : loggedinUserName
            }
            response = requests.post(url='http://127.0.0.1:5000/ordermap',json=data).content
            i=int(response.decode('ascii'))
            while(True):
                moreOrder=int(input("Enter 1 to add more orders or any other digit otherwise  : "))
                if moreOrder!=1 :
                   break
        
                item_id=int(input("Enter the item Id you want to order : "))
                plate_type=int(input("Enter 1 for half Plate or 2 for full plate : "))  
                quantity=int(input("Enter the quantity : "))  
                pt="full"
                
                if plate_type==1:
                    pt="half"
                data={
                      "orderid":i,
                      "itemno":item_id,
                      "platetype":pt,
                      "quantity":quantity,
                       
                 }
                response = requests.post(url='http://127.0.0.1:5000/insert_order',json=data).content
        
            tip=int(input("Enter the tip percent 0,10 or 20 : "))  
            people=int(input("How many people want to split bill : ")) 
            luck=int(input("Enter 1 to play test your luck discount game ,any other number otherwise : "))
            discount_percent=0
            discount_value=0.00
            if luck==1:
                arr_of_luck=[-50,-25,-25,-10,-10,-10,0,0,0,0,20,20,20,20,20,20,20,20,20,20]
                index=random.randint(0,19)
                discount_percent=arr_of_luck[index]

            data = {
            "username" : loggedinUserName,
            "orderid":i,
            "tip":tip,
            "people":people,
            "discount":discount_percent
            }

            response = requests.post(url='http://127.0.0.1:5000/getotherdetails',json=data).content
            print(response.decode('ascii'))
        
         else:
             print("You need to login first")

    elif (cho == 6):
        if loggedin==True:
            data = {
            "username" : loggedinUserName
             }
            response = requests.post(url='http://127.0.0.1:5000/previous_order',json=data).content
            print(response.decode('ascii'))
            orderid=int(input("Enter the order id whose bill you want : "))
            data = {
            "orderid":orderid,
            "username" : loggedinUserName
            }
            response = requests.post(url='http://127.0.0.1:5000/fetch_that_bill',json=data).content
            print(response.decode('ascii'))
        
        else:
             print("You need to login first")    



    elif (cho == 7):
        if(loggedin==False):
            print("You need to login first")
        elif(loggedin==True and chefLogin==False):
            print("Only chefs are allowed to do this operation")
        else:
            itemno=int(input("Enter the itemid : "))  
            halfplate=int(input("Price of halfplate : ")) 
            fullplate=int(input("Price of fullplate : "))
            data={
                "itemno":itemno,
                "halfplate":halfplate,
                "fullplate":fullplate
            }
            response = requests.post(url='http://127.0.0.1:5000/insert_menu',json=data).content
            print(response.decode('ascii'))
            

                


    else :
        break        

      