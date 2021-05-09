from pizzapi import *

customer = Customer('Chirag', 'Sethi', 'chiragsethi16@gmail.com', '6476151627')
address = Address('Apt 407-A, 253 College Street', 'Toronto', 'Ontario', 'M5T1R5')
store = address.closest_store()
order = Order(store, customer, address)

f = open("attribute.txt", "rt")
attribute = f.read()
f.close()

attribute = int(attribute)
if (attribute == 1):
    print("order 1 selected")
    order.add_item('CHSBREAD')
    order.add_item('16PANPARM')
    order.add_item('GARBUTTER')
elif attribute == 2:
    print("order 2 selected")
    order.add_item('CHSBREAD')
    order.add_item('16PANPARM')
    order.add_item('GARBUTTER')
    order.add_item('500COKE')
elif attribute == 3:
    print("order 3 selected")
    order.add_item('CHSBREAD') #cheese bread
    order.add_item('16PANPARM') #parmesan bites
    order.add_item('GARBUTTER') #roasted garlic dip
    order.add_item('GARBUTTER') #roasted garlic dip
    order.add_item('10SCVEGGIE') #10" Hand Tossed Veggie

#card = PaymentObject('4100123422343234', '0115', '777', '90210')
order.pay_with() #only for testing. won't order
print("Order placed")
