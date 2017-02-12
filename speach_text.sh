JWT="$(curl -v -X POST "https://api.cognitive.microsoft.com/sts/v1.0/issueToken" -H "Content-type: application/x-www-form-urlencoded" -H "Content-Length: 0" -H "Ocp-Apim-Subscription-Key: 4ef47af195594734be23b06e0385ba70")"

LOCALE="en-Us"
INSTANCE="565D69FF-E928-4B7E-87DA-9A750B96D9E3"
REQUEST="565D69FF-E928-4B7E-87DA-9A750B96D9E3"
OS="linux"

RESULT="$(curl -v -X POST "https://speech.platform.bing.com/recognize?scenarios=smd&appid=D4D52672-91D7-4C74-8AD8-42B1D98141A5&locale=$LOCALE&device.os=$OS&version=3.0&format=json&instanceid=$INSTANCE&requestid=$REQUEST" -H "Authorization: Bearer $JWT" -H 'Content-type: audio/wav; codec="audio/pcm"; samplerate=8000' --data-binary @output.wav)"

echo $RESULT > audio_result.txt
