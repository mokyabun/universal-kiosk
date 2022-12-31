# universal-kiosk
![preview](preview.png)

Universal Kiosk is an web ordering system with universal design.


## Universal design

- ### For blind & senior citizens
    They can operate ordering system using physical device + TTS system.

- ### For kids & locomotor disabled people
    They can scan the QR code on the main page and use web ordering system.


## Built with & Requirements

- ### Web back end
  - Python
  - Poetry (for dependency management)
  - Flask

- ### Web front end
  - Javascript
  - SvelteKit

- ### Physical device
  - #### Keypad
    - Arduino SDK
    - ESP8266 (NodeMCU)
    - ESP-NOW
    - Keypad
    - PlatformIO

  - #### Web controller
    - Selenium
    - pydub
    - pyserial

## Setup

### Clone repository to local
```bash
git clone https://github.com/krome0/universal-kiosk
```

### Web front end
```bash
cd universal-kiosk/web/front-end

npm install

npm run dev
```

### Web back end
```bash
# from project's root directory
cd web/front-end

# from front-end directory
cd ../back-end

poetry install

poetry run python main.py
```

### Physical device
- #### Keypad device
    1. Install PlatformIO on Visual Stduio Code.
    2. Open esp8266-recv, esp8266-send with PlatformIO.
    3. Build and Upload to your ESP8266(recommend NodeMCU) board.

- #### Web controller
    ```bash
    # from project's root directory
    cd physical-devices/web-controller

    poetry install

    poetry run python main.py
    ```