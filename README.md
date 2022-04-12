# How to use

1. Download the `.qbtheme` file of your taste. We recommend you download it in a **qBittorrent Themes** folder, but it is not mandatory.
2. Open **qBittorrent**, then go to *Tools -> Options* and click on the box next to *Use custom UI Theme*.
3. Right below that, browse to the path where you previously downloaded the `.qbtheme` file. Click **Apply** and then **OK**.
4. Restart **qBittorrent**. (Close it and then open it again).

# Screenshots
## Darkstylesheet.qbtheme
![darkstylesheet.qbtheme](screenshots/darkstylesheet.JPG)
## Mumble-Dark.qbtheme
![mumble-dark.qbtheme](screenshots/mumble-dark.JPG)
## Mumble-Lite.qbtheme
![mumble-lite.qbtheme](screenshots/mumble-lite.JPG)
## Breeze-Dark.qbtheme
![mumble-lite.qbtheme](screenshots/breeze-dark.JPG)

This repo contains different stylesheed edited to run with qbittorrent's style system  
DarkStyleSheet theme is based on https://github.com/ColinDuquesnoy/QDarkStyleSheet  
Mumble themes are based on https://github.com/mumble-voip/mumble-theme  
Breeze themes are based on https://github.com/Alexhuszagh/BreezeStyleSheets  
Icons used in dark themes are from nowshed-imran. They are meant to be icons for next qbittorrent major release (https://github.com/qbittorrent/qBittorrent/pull/12965). Do give your opinions on the thread :)


## How to create your own theme file?
This repo also contains different tool to create your own qbittorrent theme files.
You can check the source of above style in `Builds` folder

[qtsass](https://github.com/spyder-ide/qtsass) is a dependency of the scripts. If you don't have it, here's how to download it:
### Windows:
Download from [here](https://github.com/spyder-ide/qtsass/releases/download/0.2.2/qtsass_0.2.2_win64.zip) and extract the zip to a directory in the PATH variable, or into the directory %UserProfile%\Downloads\Compressed\qtsass_0.2.2_win64.
### Linux:
It can be installed via [Pip](https://pypi.org/project/pip/) using this command:  
`pip install git+https://github.com/spyder-ide/qtsass`  
This installs the git version of qtsass (stable release is currently broken).
