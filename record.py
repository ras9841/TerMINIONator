import alsaaudio, wave, numpy
from timeit import default_timer

def record_audio(duration):
    inp = alsaaudio.PCM(alsaaudio.PCM_CAPTURE)
    inp.setchannels(1)
    inp.setrate(44100)
    inp.setformat(alsaaudio.PCM_FORMAT_S16_LE)
    inp.setperiodsize(1024)

    w = wave.open('output.wav', 'w')
    w.setnchannels(1)
    w.setsampwidth(2)
    w.setframerate(44100)

    start = default_timer()
    while default_timer()-start < duration:
        l, data = inp.read()
        a = numpy.fromstring(data, dtype='int16')
        w.writeframes(data)
