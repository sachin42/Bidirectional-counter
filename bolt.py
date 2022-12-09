from boltiot import Bolt
import json, time, datetime,requests

API_KEY = '65eea2a7-905e-4e96-94de-5c40642e6209'
DEVICE_ID = 'BOLT8022346'

def send_msg(text):
   token = "5413429894:AAGJl2Mu-RlAvelx1yFg_0J2SYgx6Qvr0Uc"
   chat_id = "@tempraturesalert"
   url_req = "https://api.telegram.org/bot" + token + "/sendMessage" + "?chat_id=" + chat_id + "&text=" + text 
   results = requests.get(url_req)
   print(results.json())


bolt = Bolt(API_KEY, DEVICE_ID)
while True:
    data = json.loads(bolt.serialRead('10'))['value']
    print(data) 
    try:
        print("Sending message...")
        send_msg(data)
        time.sleep(1)
    except Exception as e:
        print("Error occurred: Below are the details")
        print(e)
    time.sleep(1)