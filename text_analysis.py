import sys, http.client, urllib.request, urllib.parse, urllib.error, base64, json
import serial 
import time

#phrases = {"left": 1, "right":2, "both":3, "wave":4, "dance":5, "terminator":6}

def send_commands(arduino, key_words, sentiment, full_sent):
    # lower all strings
    key_words = list(map(lambda x:x.lower(), key_words))
    full_sent = list(map(lambda x:x.lower(), full_sent.split(" ")))
    
    if len(full_sent) == 0:
        arduino.write(b'0')

    look_more = True
    for phrase in key_words:
        parts = phrase.split(" ")
        if "hands" in parts:
            arduino.write(b'3')
            look_more = False
        elif "left" in parts:
            arduino.write(b'1')
            look_more = False
        elif "right" in parts:
            arduino.write(b'2')
            look_more = False
        elif "wave" in parts or "hello" in parts or "hi" in parts or "hey" in parts:
            arduino.write(b'4')
            look_more = False
        elif "dance" in parts or "happy" in parts or "party" in parts:
            arduino.write(b'5')
            look_more = False
        elif "terminator" in parts or "connor" in parts or "danger" in parts:
            arduino.write(b'6')
            look_more = False
    if look_more:
        for part in full_sent:
            if "hands" in part: 
                arduino.write(b'3')
                look_more = False
            elif "left" in part:
                arduino.write(b'1')
                look_more = False
            elif "right" in part: 
                arduino.write(b'2')
                look_more = False
            elif "wave" in part or "hello" in part or "hi" in part or "hey" in part:
                arduino.write(b'4')
                look_more = False
            elif "dance" in part or "happy" in part or "party" in part:
                arduino.write(b'5')
                look_more = False
            elif "terminator" in part or "connor" in part or "danger" in part:
                arduino.write(b'6')
                look_more = False
    if look_more:
        arduino.write(b'0')
def get_response(response, field):
    data = json.loads(response.read().decode('utf-8'))
    results = data['documents'][0]
    return results[field]

def make_request(input_str):
    # define header post header
    headers = {
        'Content-Type': 'application/json',
        'Ocp-Apim-Subscription-Key': 'a72f2c85f0a648a483f3086aa081f4c9'
        }

    data = {"documents": [
        {
            "id": "input_request",
            "text": input_str,
            "language": "en"
        }]}
    req_body = json.dumps(data)
	
    topic_params = urllib.parse.urlencode({
        "minDocumentsPerWord": 1,
    })
    topic_data = {
        "stopWords" : [""],
        "topicsToExclude" : [""],
        "documents": [
        {
            "id": "input_request",
            "text": input_str,
            "language": "en"
        }]}
    topic_body = json.dumps(data)

    try:
        conn = http.client.HTTPSConnection('westus.api.cognitive.microsoft.com')
		
        # Get key phrases
        conn.request("POST", "/text/analytics/v2.0/keyPhrases", req_body, headers)
        response = conn.getresponse()
        key_phrases = get_response(response, "keyPhrases")
		
        # Get sentiment
        conn.request("POST", "/text/analytics/v2.0/sentiment", req_body, headers)
        response = conn.getresponse()
        sentiment = get_response(response, "score")
	
        conn.close()
		
        # Print results
        #print("Key Phrases: ",key_phrases)
        #print("Sentiment Score: ",sentiment)
        return key_phrases, sentiment
    except Exception as e:
        print(e)
        return None, None

def run_analysis():
    arduino = serial.Serial('/dev/ttyACM0', 9600)
    time.sleep(3)
    f = open("audio_result.txt","r")
    audio_result = f.readline()
    f.close()
    try:
        u_input = json.loads(audio_result)["header"]["name"]
        print("User Input: %s"%(u_input)) 
        key_phrases, sentiment = make_request(u_input)
        print(key_phrases)
        send_commands(arduino, key_phrases, sentiment, str(u_input)) 
        return str(u_input)
    except Exception as e:
        print(e)
        return None

if __name__ == "__main__":
    run_analysis()
