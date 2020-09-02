from cs50 import get_int


def main():
    cardNumber = getCardNumber()
    if isValid(cardNumber):
        print(f"{ company(getStartingDigtis(cardNumber)) }")
        return 0
        
    print('INVALID')
    return 1
  
    
def getCardNumber():
    while (True):
        cardNumber = get_int("Number: ")
        if cardNumber > 0:
            break
    
    return cardNumber


def digitsCount(number):
    counter = 0
    while (number > 0):
        number = int(number / 10)
        counter += 1
    
    return counter


def isValid(number):
    # Check quantity of digits, should be 13 <= digitsCount >= 16
    digits = digitsCount(number)
    if digits < 13 or digits > 16:
        return False
    
    # Checksum algorithm
    position = 1
    everyOtherSum = 0
    remainingDigitsSum = 0
    
    while (number > 0):
        if (position % 2) == 0:
            everyOtherSum += digitsSum((number % 10) * 2)
        else:
            remainingDigitsSum += number % 10
        
        number = int(number / 10)
        position += 1
    
    if ((everyOtherSum + remainingDigitsSum) % 10) == 0:
        return True
    
    return False
    
    
def digitsSum(number):
    s = 0
    while (number > 0):
        s += number % 10
        number = int(number / 10)
    
    return s
    
    
def getStartingDigtis(number):
    remainder = 0
    while (number > 10):
        remainder = number % 100
        number = int(number / 10)
    
    return remainder


def company(i):
    switcher = {
        34: 'AMEX',
        37: 'AMEX',
        51: 'MASTERCARD',
        52: 'MASTERCARD',
        53: 'MASTERCARD',
        54: 'MASTERCARD',
        55: 'MASTERCARD',
        40: 'VISA',
        41: 'VISA',
        42: 'VISA',
        43: 'VISA',
        44: 'VISA',
        45: 'VISA',
        46: 'VISA',
        47: 'VISA',
        48: 'VISA',
        49: 'VISA',
    }
    
    return switcher.get(i, 'INVALID')

        
main()    