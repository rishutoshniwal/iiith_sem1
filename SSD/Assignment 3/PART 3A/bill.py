import csv
import random


def merge_same_order_and_print(ids,plate_type_list,item_price,item_quantity):
     '''to add same orders (same item and same plate type)
        and print detailed bill
         '''
         
     # merge same orders     
     for i in range(0,len(ids),1):
         for j in range(i+1,len(ids),1):
             if ids[i]!=-1 and ids[i]==ids[j] and plate_type_list[i]==plate_type_list[j] :
                 ids[j]=-1
                 item_price[i]=item_price[i]+item_price[j]
                 item_quantity[i]=item_quantity[i]+item_quantity[j]
                 item_price[j]=0
                 item_quantity[j]=0
     
      # print detailed bills
     for x in range(len(ids)):  
         if ids[x]!=-1 :
             if plate_type_list[x]==1:
                   print("Item "+str(ids[x])+" [half]["+str(item_quantity[x])+"] : "+str(item_price[x]))  
             else:     
                  print("Item "+str(ids[x])+" [full]["+str(item_quantity[x])+"] : "+str(item_price[x]))
   


def customer_win_pattern():
     '''when customer gets lucky discount,
        this pattern is printed '''
     
     print("\n **** \t\t **** \n|    |\t\t|    |\n|    |\t\t|    |\n|    |\t\t|    |\n **** \t\t **** \n")
     print("\t  {}\n\t ____\n")

def customer_lose_pattern():   
     '''when customer lose in lucky discount,
        this pattern is printed
      '''
     print("\n **** \n*    *\n*    *\n*    *\n*    *\n **** \n") 

def get_tip():
     '''
     tip percentage has fixed choice,
     keep taking input till customer enter valid value
     '''
     
     tip=int(input("Enter the tip percent 0,10 or 20 : "))  
     if tip==0 or tip==10 or tip==20:
          return tip
     else :
         print("Invalid value of tip,please enter again from the options")
         return get_tip()
        
    
 
# opening the CSV file
with open('menu.csv', mode ='r')as file:
   
  # reading the CSV file
  csvFile = csv.reader(file)
 
   # lists to store menu details
  item=[]
  half=[]
  full=[]
  
  
  i=0
  menu_head=""
  for lines in csvFile:
      if i!=0 :
          item.append(int(lines[0]))
          half.append(int(lines[1]))
          full.append(int(lines[2]))
      else:
          menu_head=menu_head+lines[0]+"\t\t"+lines[1]+"\t\t"+lines[2]
          
      i=i+1 
      
# lists to store details of ordered items 
ids=[]
item_quantity=[]
item_price=[]
plate_type_list=[]

# display the menu in csv file 
print(menu_head)
for x in range(len(item)):
    
       list_of_items="{0:^7}".format(str(item[x]))
       price_of_half="{0:^10}".format(str(half[x]))
       price_of_full="{0:^10}".format(str(full[x]))
      
       print(list_of_items+"\t\t"+price_of_half+"\t\t"+price_of_full)
  
'''   Test Docstrings
print(customer_win_pattern.__doc__)
print(customer_lose_pattern.__doc__)
print(get_tip.__doc__)
print(merge_same_order_and_print.__doc__)
'''

total_cost_of_all_items=0.00     

# add your order
while(True):
     moreOrder=int(input("Enter 1 to add more orders or any other digit otherwise  : "))
     if moreOrder!=1 :
         break
       
     item_id=int(input("Enter the item Id you want to order : "))
     plate_type=int(input("Enter 1 for half Plate or 2 for full plate : "))  
     quantity=int(input("Enter the quantity : "))  
     
     
     ids.append(item_id)
     item_quantity.append(quantity)
     plate_type_list.append(plate_type)

     if plate_type==1 :
         price_of_this_item=half[item_id-1]*quantity
         item_price.append(price_of_this_item)
         total_cost_of_all_items=total_cost_of_all_items+price_of_this_item
     else :
          
         price_of_this_item=full[item_id-1]*quantity
         item_price.append(price_of_this_item)
         total_cost_of_all_items=total_cost_of_all_items+price_of_this_item
     

# input tip percentage
tip=get_tip() 
amount_with_tip=(total_cost_of_all_items * (100+tip))/100
print("amount_with_tip to be paid (including tip ) is : "+'%.2f'%amount_with_tip)     

# input number of people to split bill
people=int(input("How many people want to split bill : ")) 
cost_per_head=amount_with_tip/people
print ("amount_with_tip to be paid per menu_head : "+'%.2f'%cost_per_head)

# luck based game
luck=int(input("Enter 1 to play test your luck discount game ,any other number otherwise : "))

# bill manipulations based on luck game
discount_percent=0
discount_value=0.00
if luck==1:
      arr_of_luck=[-50,-25,-25,-10,-10,-10,0,0,0,0,20,20,20,20,20,20,20,20,20,20]
      index=random.randint(0,19)
      discount_percent=arr_of_luck[index]
      
      if(arr_of_luck[index]<0):
          customer_win_pattern()
         
      else:
          customer_lose_pattern()
          
      discount_value=(amount_with_tip * discount_percent)/100
      amount_with_tip=amount_with_tip+discount_value
      
      
# printing detailed bill
merge_same_order_and_print(ids,plate_type_list,item_price,item_quantity)

print("total_cost_of_all_items : " + '%.2f'%total_cost_of_all_items)
print("Tip percentage : "+str(tip))
print("Discount/Increase : "+'%.2f'%discount_value)
cost_per_head=amount_with_tip/people
print("Final total_cost_of_all_items : "+'%.2f'%amount_with_tip)
print ("Updated amount_with_tip to be paid per menu_head : "+'%.2f'%cost_per_head)
     

      