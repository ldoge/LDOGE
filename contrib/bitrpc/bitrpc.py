from jsonrpc import ServiceProxy
import sys
import string

# ===== BEGIN USER SETTINGS =====
# if you do not set these you will be prompted for a password for every command
rpcuser = ""
rpcpass = ""
# ====== END USER SETTINGS ======


if rpcpass == "":
	access = ServiceProxy("http://127.0.0.1:8332")
else:
	access = ServiceProxy("http://"+rpcuser+":"+rpcpass+"@127.0.0.1:8332")
cmd = sys.argv[1].lower()

if cmd == "backupwallet":
	try:
		path = input("Enter destination path/filename: ")
		print(access.backupwallet(path))
	except:
		print("\n---An error occurred---\n")

elif cmd == "getaccount":
	try:
		addr = input("Enter a Bitcoin address: ")
		print(access.getaccount(addr))
	except:
		print("\n---An error occurred---\n")

elif cmd == "getaccountaddress":
	try:
		acct = input("Enter an account name: ")
		print(access.getaccountaddress(acct))
	except:
		print("\n---An error occurred---\n")

elif cmd == "getaddressesbyaccount":
	try:
		acct = input("Enter an account name: ")
		print(access.getaddressesbyaccount(acct))
	except:
		print("\n---An error occurred---\n")

elif cmd == "getbalance":
	try:
		acct = input("Enter an account (optional): ")
		mc = input("Minimum confirmations (optional): ")
		try:
			print(access.getbalance(acct, mc))
		except:
			print(access.getbalance())
	except:
		print("\n---An error occurred---\n")

elif cmd == "getblockbycount":
	try:
		height = input("Height: ")
		print(access.getblockbycount(height))
	except:
		print("\n---An error occurred---\n")

elif cmd == "getblockcount":
	try:
		print(access.getblockcount())
	except:
		print("\n---An error occurred---\n")

elif cmd == "getblocknumber":
	try:
		print(access.getblocknumber())
	except:
		print("\n---An error occurred---\n")

elif cmd == "getconnectioncount":
	try:
		print(access.getconnectioncount())
	except:
		print("\n---An error occurred---\n")

elif cmd == "getdifficulty":
	try:
		print(access.getdifficulty())
	except:
		print("\n---An error occurred---\n")

elif cmd == "getgenerate":
	try:
		print(access.getgenerate())
	except:
		print("\n---An error occurred---\n")

elif cmd == "gethashespersec":
	try:
		print(access.gethashespersec())
	except:
		print("\n---An error occurred---\n")

elif cmd == "getinfo":
	try:
		print(access.getinfo())
	except:
		print("\n---An error occurred---\n")

elif cmd == "getnewaddress":
	try:
		acct = input("Enter an account name: ")
		try:
			print(access.getnewaddress(acct))
		except:
			print(access.getnewaddress())
	except:
		print("\n---An error occurred---\n")

elif cmd == "getreceivedbyaccount":
	try:
		acct = input("Enter an account (optional): ")
		mc = input("Minimum confirmations (optional): ")
		try:
			print(access.getreceivedbyaccount(acct, mc))
		except:
			print(access.getreceivedbyaccount())
	except:
		print("\n---An error occurred---\n")

elif cmd == "getreceivedbyaddress":
	try:
		addr = input("Enter a Bitcoin address (optional): ")
		mc = input("Minimum confirmations (optional): ")
		try:
			print(access.getreceivedbyaddress(addr, mc))
		except:
			print(access.getreceivedbyaddress())
	except:
		print("\n---An error occurred---\n")

elif cmd == "gettransaction":
	try:
		txid = input("Enter a transaction ID: ")
		print(access.gettransaction(txid))
	except:
		print("\n---An error occurred---\n")

elif cmd == "getwork":
	try:
		data = input("Data (optional): ")
		try:
			print(access.gettransaction(data))
		except:
			print(access.gettransaction())
	except:
		print("\n---An error occurred---\n")

elif cmd == "help":
	try:
		cmd = input("Command (optional): ")
		try:
			print(access.help(cmd))
		except:
			print(access.help())
	except:
		print("\n---An error occurred---\n")

elif cmd == "listaccounts":
	try:
		mc = input("Minimum confirmations (optional): ")
		try:
			print(access.listaccounts(mc))
		except:
			print(access.listaccounts())
	except:
		print("\n---An error occurred---\n")

elif cmd == "listreceivedbyaccount":
	try:
		mc = input("Minimum confirmations (optional): ")
		incemp = input("Include empty? (true/false, optional): ")
		try:
			print(access.listreceivedbyaccount(mc, incemp))
		except:
			print(access.listreceivedbyaccount())
	except:
		print("\n---An error occurred---\n")

elif cmd == "listreceivedbyaddress":
	try:
		mc = input("Minimum confirmations (optional): ")
		incemp = input("Include empty? (true/false, optional): ")
		try:
			print(access.listreceivedbyaddress(mc, incemp))
		except:
			print(access.listreceivedbyaddress())
	except:
		print("\n---An error occurred---\n")

elif cmd == "listtransactions":
	try:
		acct = input("Account (optional): ")
		count = input("Number of transactions (optional): ")
		frm = input("Skip (optional):")
		try:
			print(access.listtransactions(acct, count, frm))
		except:
			print(access.listtransactions())
	except:
		print("\n---An error occurred---\n")

elif cmd == "move":
	try:
		frm = input("From: ")
		to = input("To: ")
		amt = input("Amount:")
		mc = input("Minimum confirmations (optional): ")
		comment = input("Comment (optional): ")
		try:
			print(access.move(frm, to, amt, mc, comment))
		except:
			print(access.move(frm, to, amt))
	except:
		print("\n---An error occurred---\n")

elif cmd == "sendfrom":
	try:
		frm = input("From: ")
		to = input("To: ")
		amt = input("Amount:")
		mc = input("Minimum confirmations (optional): ")
		comment = input("Comment (optional): ")
		commentto = input("Comment-to (optional): ")
		try:
			print(access.sendfrom(frm, to, amt, mc, comment, commentto))
		except:
			print(access.sendfrom(frm, to, amt))
	except:
		print("\n---An error occurred---\n")

elif cmd == "sendmany":
	try:
		frm = input("From: ")
		to = input("To (in format address1:amount1,address2:amount2,...): ")
		mc = input("Minimum confirmations (optional): ")
		comment = input("Comment (optional): ")
		try:
			print(access.sendmany(frm,to,mc,comment))
		except:
			print(access.sendmany(frm,to))
	except:
		print("\n---An error occurred---\n")

elif cmd == "sendtoaddress":
	try:
		to = input("To (in format address1:amount1,address2:amount2,...): ")
		amt = input("Amount:")
		comment = input("Comment (optional): ")
		commentto = input("Comment-to (optional): ")
		try:
			print(access.sendtoaddress(to,amt,comment,commentto))
		except:
			print(access.sendtoaddress(to,amt))
	except:
		print("\n---An error occurred---\n")

elif cmd == "setaccount":
	try:
		addr = input("Address: ")
		acct = input("Account:")
		print(access.setaccount(addr,acct))
	except:
		print("\n---An error occurred---\n")

elif cmd == "setgenerate":
	try:
		gen= input("Generate? (true/false): ")
		cpus = input("Max processors/cores (-1 for unlimited, optional):")
		try:
			print(access.setgenerate(gen, cpus))
		except:
			print(access.setgenerate(gen))
	except:
		print("\n---An error occurred---\n")

elif cmd == "settxfee":
	try:
		amt = input("Amount:")
		print(access.settxfee(amt))
	except:
		print("\n---An error occurred---\n")

elif cmd == "stop":
	try:
		print(access.stop())
	except:
		print("\n---An error occurred---\n")

elif cmd == "validateaddress":
	try:
		addr = input("Address: ")
		print(access.validateaddress(addr))
	except:
		print("\n---An error occurred---\n")

elif cmd == "walletpassphrase":
	try:
		pwd = input("Enter wallet passphrase: ")
		access.walletpassphrase(pwd, 60)
		print("\n---Wallet unlocked---\n")
	except:
		print("\n---An error occurred---\n")

elif cmd == "walletpassphrasechange":
	try:
		pwd = input("Enter old wallet passphrase: ")
		pwd2 = input("Enter new wallet passphrase: ")
		access.walletpassphrasechange(pwd, pwd2)
		print("")
		print("\n---Passphrase changed---\n")
	except:
		print("")
		print("\n---An error occurred---\n")
		print("")

else:
	print("Command not found or not supported")
