from jsonrpc import ServiceProxy
access = ServiceProxy("http://127.0.0.1:8332")
pwd = input("Enter old wallet passphrase: ")
pwd2 = input("Enter new wallet passphrase: ")
if pwd2 == "":
  print("Your about to remove the password of your wallet are you sure about this?")
  while True:
    awnser = input("Y or N: ")
    if awnser == "Y":
      access.walletpassphrasechange(pwd, pwd2)
      break
    elif awnser == "N":
      print("Stopped changes")
      break
    else:
      print("Please awnser only with Y or N")
else:
  access.walletpassphrasechange(pwd, pwd2)
      
