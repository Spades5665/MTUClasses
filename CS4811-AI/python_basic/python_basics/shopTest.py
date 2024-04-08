import shop

shopName = 'Jims'
fruitPrices = {'apples': 1.00, 'oranges': 1.50, 'pears': 1.75}
jimsShop = shop.FruitShop(shopName, fruitPrices)
applePrice = jimsShop.getCostPerPound('apples')
print(applePrice)
print('Apples cost $%.2f at %s.' % (applePrice, shopName))

otherName = 'EconoFoods'
otherFruitPrices = {'kiwis':6.00, 'apples': 4.50, 'peaches': 8.75}
otherFruitShop = shop.FruitShop(otherName, otherFruitPrices)
otherPrice = otherFruitShop.getCostPerPound('apples')
print(otherPrice)
print('Apples cost $%.2f at %s.' % (otherPrice, otherName))
print("My, that's expensive!")