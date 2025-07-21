# 3D Particle Life
 A Linux-based artificial life simulation built with [OpenFrameworks](https://openframeworks.cc/), where simple attraction and repulsion rules lead to complex, emergent behavior inspired by cellular automata.
 
## Features
- Real-time parameter tweaking via GUI
- Save and load custom presets
- Keyboard shortcuts for fast control
- Visual feedback and smooth particle dynamics

### Note
After saving a preset you need to restart the app in order to see it. This is because the dropdown addon is really buggy and there is nothing I can do about it.

## SETUP
### Linux
- [Download OpenFrameworks](https://openframeworks.cc/download/)
- [Follow these steps](https://openframeworks.cc/setup/linux-install/)
- Make sure you install Project Generator

 If you see the following error:

```bash
/usr/bin/ld.gold: error: cannot find -lXi
/usr/bin/ld.gold: error: cannot find -lXcursor
/usr/bin/ld.gold: error: cannot find -lXinerama
```
run 
``` 
sudo apt-get install libxi-dev libxcursor-dev libxinerama-dev
```

- Also you need to download this openFrameworks [ofxDropdown](https://github.com/roymacdonald/ofxDropdown) addon. 
- After cloning this repository, use **Project Generator** to create a new project and choose to import from the downloaded folder, in order to be able to run the code.
- Make sure you add the **ofxGui** and **ofxDropdown** addons from the Project Generator. 

---
#### TO DO:
- Faster Rendering (shaders)
  
#### BUG FIXES
- if all 3 of the same color radius is 0 then fps drops dramatically. Alla ama kaneis restart gia kapoion logo ftiaxnei
