import hashlib
from socket import *
serverName = 'localhost'
serverPort = 10000
clientSocket = socket(AF_INET, SOCK_DGRAM)

clientsA = ("0xA0000001", "0xA0000002")
clientsB = ("0xB0000001", "0xB0000002")

with open("balancesA.txt", 'w') as writer:
    message = "0xA0000001 0x000003E8 0x000003E8 0xA0000002 0x000003E8 0x000003E8"
    writer.write(message)

with open("clientA_unconfirmed.txt", 'w') as writer:
    writer.write("")


def new_transaction(sender, payee, payment):
    with open("clientA_unconfirmed.txt", 'a') as ap:
        tx_message = f"{sender} {payee} {hex(payment)} "
        ap.write(tx_message)
        clientSocket.sendto(tx_message.encode(), (serverName, serverPort))


def check_amount(account, amount):
    i = 0
    with open('balancesA.txt', 'r') as reader:
        account_balances = reader.read().split(" ")
        for words in account_balances:
            if words == account:
                if (amount + 2) <= int(account_balances[i+1], 16):
                    newAmount = hex(int(account_balances[i+1], 16) - amount)
                    account_balances[i+1] = newAmount
                    with open("balancesA.txt", 'w') as writer:
                        for lines in account_balances:
                            writer.write(lines + " ")
                    return True
                else:
                    print("Insufficient funds, please enter again...")
                    return False
            else:
                i += 1

def updateList(FileName):
    with open(FileName, 'r') as reader:
        lines = reader.read().split(" ")
        return lines

while 1:
    print('''
1: Enter a new transaction.
2: The current balance for each account.
3: Print the unconfirmed transactions.
4: Print the confirmed transactions.
5: Print the blockchain.
6: Exit. ''')
    choice = input("Choice: ")

    if choice == "1": # New Transaction
        print("Option 1 chosen...")
        i = ''
        while 1:
            print("Select the Payer:")
            print("1. A0000001")
            print("2. A0000002")
            i = int(input("Choice: "))
            if i == 1 or i == 2:
                break
        payer = clientsA[i - 1]

        while 1:
            print("Select the Payer:")
            print("1. B0000001")
            print("2. B0000002")
            i = int(input("Choice: "))
            if i == 1 or i == 2:
                break

        receiver = clientsB[i - 1]
        while 1:
            print("Enter the amount of payment in decimal.")
            payAmount = int(input(">"))
            if check_amount(payer, payAmount):
                break

        Tx_message = f"Tx: {payer} pays {receiver} the amount of {payAmount} BC."
        print(Tx_message)
        new_transaction(payer, receiver, payAmount)

    elif choice == "2": # Current balance of each account
        print("Option 2 chosen...")

        with open("balancesA.txt", "r") as reader:
            tx_list = reader.read().split(" ")
            print(f"Account {tx_list[0]} has {tx_list[1]} BC")
            print(f"Account {tx_list[3]} has {tx_list[4]} BC")

    elif choice == "3": # Unconfirmed transaction
        print("Option 3 chosen...")
        i = 0
        with open("clientA_unconfirmed.txt", 'r') as reader:
            unconfirmed_tx = reader.read().split(" ")
            for line in unconfirmed_tx:
                if line == clientsA[0] or line == clientsA[1]:
                    print(f"TX: {unconfirmed_tx[i]} pays {unconfirmed_tx[i + 1]} the amount of {unconfirmed_tx[i + 2]} BC")
                    i += 1
                else:
                    i += 1

    elif choice == "4": # Confirmed transaction
        print("Option 4 chosen...")
        i = 0
        with open("clientA_confirmed.txt", 'r') as reader:
            confirmed_tx = reader.read().split(" ")
            for line in confirmed_tx:
                if line == clientsA[0] or line == clientsA[1]:
                    print(f"TX: {confirmed_tx[i]} pays {confirmed_tx[i + 1]} the amount of {confirmed_tx[i + 2]} BC")
                    i += 1
                else:
                    i += 1

    elif choice == "5": # Print Block Chain
        print("Option 5 chosen...")
        i = 0
        x = 1
        BCP = updateList('blockchain_f1.txt')
        NUMELEMS = len(BCP)
        print(BCP)
        while (i < NUMELEMS):
            print("Block: " + str(x))
            x += 1
            print("Nonce (4-byte): " + BCP[i])
            i += 1
            print("Last Block hash (32-byte): " + BCP[i])
            i += 1
            print("Merkle root (32-byte): " + BCP[i])
            i += 1

        i = 0
        TXP = updateList('blockchain_f1.txt')
        NUMELEMS = len(TXP)
        while (i < NUMELEMS - 1):
            print("Tx" + str(i) + " (12-byte): " + TXP[i] + " paid " + TXP[i + 1] + " the amount of " + TXP[i + 2] + " BC.")
            i += 3
    elif choice == "6": # Exit
        print("Exiting...")
        break
    else:
        print("Invalid entry, please try again...")

clientSocket.close()
