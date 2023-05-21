import os
import requests
import base64
def dreamstudio_main(ask):

    print(ask)
    engine_id = "stable-diffusion-v1-5"
    #api_host = os.getenv('API_HOST', 'https://api.stability.ai')
    #api_key = os.getenv("sk-wFnlChlCAX2geVAgBsDwDXmECixrVwY5xPcC5lmwjCEDJBvj")

    #if api_key is None:
        #raise Exception("Missing Stability API key.")

    response = requests.post(
        f"https://api.stability.ai/v1/generation/stable-diffusion-v1-5/text-to-image",
        headers={
            "Content-Type": "application/json",
            "Accept": "application/json",
            "Authorization": f"Bearer sk-wFnlChlCAX2geVAgBsDwDXmECixrVwY5xPcC5lmwjCEDJBvj"
        },
        json={
            "text_prompts": [
                {
                    "text": ask
                }
            ],
            "cfg_scale": 7,
            "clip_guidance_preset": "FAST_BLUE",
            "height": 512,
            "width": 512,
            "samples": 1,
            "steps": 50,
        },
    )

    if response.status_code != 200:
        raise Exception("Non-200 response: " + str(response.text))

    data = response.json()
    #print(data)
    #data = response.json()
    base64_string = data['artifacts'][0]['base64']
    #for image in enumerate(data["artifacts"]):
    with open(f"./resource/picture/out.png", "wb") as f:
        f.write(base64.decodebytes(bytes(base64_string, encoding='utf8')))
    f.close()
    return "D:\\QBot\\resource\\picture\\out.png"

if __name__ == "__main__":
    print(dreamstudio_main("god father"))
