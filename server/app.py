from flask import Flask, request, jsonify
import openai
import base64
import os
import speech_recognition as sr
from gtts import gTTS
import playsound

app = Flask(__name__)

# OpenAI API Key
openai.api_key = "your_openai_api_key"

@app.route('/analyze', methods=['POST'])
def analyze_image():
    image_data = request.data  # Receiving the image

    # Save image temporarily
    image_path = "captured.jpg"
    with open(image_path, "wb") as f:
        f.write(image_data)

    # Convert image to base64 for API
    with open(image_path, "rb") as image_file:
        base64_image = base64.b64encode(image_file.read()).decode('utf-8')

    # Send to GPT-4-Vision API
    response = openai.ChatCompletion.create(
        model="gpt-4-vision-preview",
        messages=[{"role": "user", "content": f"What do you see in this image? {base64_image}"}]
    )

    description = response["choices"][0]["message"]["content"]
    
    # Convert text to speech
    tts = gTTS(text=description, lang='en')
    audio_path = "response.mp3"
    tts.save(audio_path)
    playsound.playsound(audio_path)

    return jsonify({"description": description})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
