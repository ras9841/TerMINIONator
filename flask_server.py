from flask import Flask
from flask import render_template, request, url_for, redirect
import sys, os
from record import record_audio
from text_analysis import run_analysis

app = Flask(__name__)


@app.route('/record', methods=['GET', 'POST'])
def record():
    record_audio(5.0)
    os.system("sh speach_text.sh")
    uinput = run_analysis()
    return redirect(url_for('index', uinput=uinput))

@app.route('/')
@app.route('/<uinput>')
def index(uinput = None):
    return render_template('index.html', uinput=uinput)

if __name__ == "__main__":
    app.run()
