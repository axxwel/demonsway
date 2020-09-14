# Demon's way.
Match-3 game

## Tools.
- Macos Catalina 10.15.6
- Xcode 10.6
- cocos2d-x 4.0

## Install.
  ### Intstall xcode.
  https://apps.apple.com/fr/app/xcode/id497799835?mt=12
  ### Install cocos2dx latest version.
  https://www.cocos.com/en/cocos2dx/download

  ```
  cd [ENGINE DIRECTORY]/cocos2d-4.0/python ./setup.py
  cocos new demonsway -p com.axxwel.demonsway -l cpp -d [GAME DIRECTORY]/demonsway
  ```
  
  ### Install CMake
  Install homebrew
  ```
  /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
  ```

  Install cmake
  ```
  brew install cmake
  ```
  ### Init xcodeproj
  ```
  cd [GAME DIRECTORY]/demonsway
  mkdir ios-build && cd ios-build
  cmake .. -GXcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphoneos
  ```

  CMake error: iphoneos is not an iOS SDK
  ```
  sudo xcode-select -switch /Applications/Xcode.app/Contents/Developer 
  cmake .. -GXcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphoneos
  ```
