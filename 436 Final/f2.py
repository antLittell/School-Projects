from socket import *
import hashlib
import os
serverPort = 11000
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('', serverPort))
print('The server is ready to receive')
serverName = 'localhost'
b_receive = 21000
f1_node = 10000

HashList = ["000000000000000000000000", "000000000000000000000000", "000000000000000000000000", "000000000000000000000000"]
nonce = 0
Empty = ""
LB = "0000000000000000000000000000000000000000000000000000000000000000"


def Hashing(Tx, Nonce, LastBlock, MerkleRoot):
    hashHandler = hashlib.sha256() #length of hash number 256 bits 32-byte HEX
    nonce = 0 #nonce
    while True: #infinte loop
        block_header = Tx + Nonce + LastBlock + MerkleRoot#the thing being hashed
        hashHandler.update(block_header.encode("utf-8")) #encode
        hashValue = hashHandler.hexdigest() #contain only HEX numbers
        #print('nonce:{0}, hash:{1}'.format(nonce, hashValue)) #print format
        nounceFound = True
        for i in range(4): #amount of leading zeros
            if hashValue[i]!='0': #leading number
                nounceFound = False
        if nounceFound: #escapes once leading 4 zeros
            if(Tx == ""):
                f = open('blockchain_f2.txt', 'a')
                f.write(str(nonce) + " " + LastBlock + " " + MerkleRoot + " ")
                f.close()
            break
        else: #keeps going in loop until leading 4 zeros
            nonce = nonce + 1
    return hashValue


with open("balancesF.txt", 'w') as writer:
    message = "0xF0000001 0x00000000 0xF0000002 0x00000000"
    writer.write(message)

with open("temp_tx_f2.txt", "w") as writer:
    writer.write(" ")

with open("blockchain_f2.txt", "w") as writer:
    writer.write(" ")

num_of_tx = 0
num_of_blocks = 0


def tx_check(tx_list):
    if tx_list[0:10] == "0xA0000001" or tx_list[0:10] == "0xA0000002" or tx_list[0:10] == "0xB0000001" or tx_list[0:10] == "0xB0000002":
        return True
    return False


def send_to_node(node_message):
    serverSocket.sendto(node_message.encode(), (serverName, f1_node))


def send_to_client(client_message):
    serverSocket.sendto(client_message.encode(), (serverName, b_receive))


while 1:
    message, clientAddress = serverSocket.recvfrom(2048)
    modifiedMessage = message.decode()

    # if from other node
    if clientAddress[1] == f1_node:
        print("from f1")

        # if it is a transaction
        if tx_check(modifiedMessage):
            print("this is a transaction")

            # appends to the temp transaction file
            with open("temp_tx_f2.txt", "a") as ap:
                ap.write(modifiedMessage + " ")
                num_of_tx += 1
                if num_of_tx % 4 == 0:
                    num_of_blocks += 1
                    with open("temp_tx_f2.txt", "r") as reader:
                        message = reader.read()
                        send_to_client(message)
            print(f"{num_of_tx} {num_of_blocks}")

            # if it is this nodes turn to mine a block
            if num_of_blocks % 2 == 0 and num_of_blocks != 0 and num_of_tx%4 == 0:
                print("Beginning mine...")
                with open("temp_tx_f2.txt", "r") as reader:
                    temp_txs = reader.read().split(" ")
                with open("temp_tx_f2.txt", "w") as writer:
                    writer.write(" ")

                # mining function goes here
                i = 0
                while i < 4:
                    HashList[i] = Hashing(temp_txs[i], Empty, Empty, Empty)
                    i += 1

                A = HashList[0]
                B = HashList[1]
                C = HashList[2]
                D = HashList[3]
                AB = A + B
                CD = C + D
                AB = Hashing(AB, Empty, Empty, Empty)
                CD = Hashing(CD, Empty, Empty, Empty)
                ABCD = AB + CD
                ABCD = Hashing(ABCD, Empty, Empty, Empty)

                if os.stat("blockchain_f2.txt").st_size != 0:
                    print("checkpoint 1 made")
                    with open('blockchain_f2.txt', 'r') as reader:
                        BlockChain = reader.read().split(" ")
                        NUMELEMS = len(BlockChain)
                        LB = BlockChain[NUMELEMS - 2]

                Hashing(Empty, str(nonce), LB, ABCD)

                # updates the account with the appropriate amount of BC
                with open("balancesF.txt", "r") as reader:
                    account_balances = reader.read().split(" ")
                    i = 0
                    for accounts in account_balances:
                        if accounts == "0xF0000002":
                            print("checkpoint 2")
                            account_balances[i + 1] = hex(int(account_balances[i + 1], 16) + 38)
                            with open("balancesF.txt", "w") as writer:
                                for lines in account_balances:
                                    writer.write(lines + " ")
                        else:
                            i += 1
                with open("blockchain_f2.txt", 'r') as reader:
                    print("checkpoint 3")
                    tx_block = reader.read()
                    send_to_node(tx_block)

        else:
            print("must be block")
            with open("blockchain_f2.txt", "a") as ap:
                print("testing 123")
                ap.write(modifiedMessage)

    # if from the client
    else:
        print("from client")

        #append to the temp transaction file
        with open("temp_tx_f2.txt", "a") as ap:
            ap.write(modifiedMessage + " ")
            num_of_tx += 1
            if num_of_tx%4 == 0:
                num_of_blocks += 1
                with open("temp_tx_f2.txt", "r") as reader:
                    message = reader.read()
                    send_to_client(message)
        send_to_node(modifiedMessage)
        print(f"{num_of_tx} {num_of_blocks}")

        if num_of_blocks%2 == 0 and num_of_blocks != 0 and num_of_tx%4 == 0:
            print("Beginning mine...")
            with open("temp_tx_f2.txt", "r") as reader:
                temp_txs = reader.read().split(" ")
            with open("temp_tx_f2.txt", "w") as writer:
                writer.write(" ")

            # mining function goes here
            i = 0
            while i < 4:
                HashList[i] = Hashing(temp_txs[i], Empty, Empty, Empty)
                i += 1

            A = HashList[0]
            B = HashList[1]
            C = HashList[2]
            D = HashList[3]
            AB = A + B
            CD = C + D
            AB = Hashing(AB, Empty, Empty, Empty)
            CD = Hashing(CD, Empty, Empty, Empty)
            ABCD = AB + CD
            ABCD = Hashing(ABCD, Empty, Empty, Empty)

            if os.stat("blockchain_f2.txt").st_size != 0:
                print("checkpoint 1")
                with open('blockchain_f2.txt', 'r') as reader:
                    BlockChain = reader.read().split(" ")
                    NUMELEMS = len(BlockChain)
                    LB = BlockChain[NUMELEMS - 2]

            Hashing(Empty, str(nonce), LB, ABCD)

            with open("balancesF.txt", "r") as reader:
                account_balances = reader.read().split(" ")
                i = 0
                for accounts in account_balances:
                    if accounts == "0xF0000001":
                        print("Checkpoint 2")
                        account_balances[i+1] = hex(int(account_balances[i+1], 16) + 38)
                        with open("balancesF.txt", "w") as writer:
                            for lines in account_balances:
                                writer.write(lines + " ")
                    else:
                        i += 1
            with open("blockchain_f2.txt", 'r') as reader:
                print("made it to checkpoint 3")
                tx_block = reader.read()
            send_to_node(tx_block)

            # send block to other node here
            # print block here