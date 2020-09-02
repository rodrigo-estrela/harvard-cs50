from cs50 import get_float


def main():
    numberOfCoins = 0
    owedChange = get_change()
    
    # Check how many quartes
    if (owedChange >= 25):
        numberOfCoins += int(owedChange / 25)
        owedChange = owedChange % 25
        if owedChange == 0:
            print(f"{numberOfCoins}")
            return 0
    
    # Check how many dimes
    if (owedChange >= 10):
        numberOfCoins += int(owedChange / 10)
        owedChange = owedChange % 10
        if owedChange == 0:
            print(f"{numberOfCoins}")
            return 0
            
    # Check how many nickles
    if (owedChange >= 5):
        numberOfCoins += int(owedChange / 5)
        owedChange = owedChange % 5
        if owedChange == 0:
            print(f"{numberOfCoins}")
            return 0
            
    print(f"{int(numberOfCoins + owedChange / 1)}")


def get_change():
    while (True):
        change = get_float("Change owed: ")
        if change > 0:
            break
    
    return int(change * 100)


main()