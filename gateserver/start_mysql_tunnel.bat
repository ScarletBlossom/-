@echo off
setlocal

set SSH_USER=libaya
set SSH_HOST=47.122.135.202
set LOCAL_PORT=3307
set REMOTE_PORT=3306

echo Starting SSH tunnel to %SSH_HOST%...

ssh -L %LOCAL_PORT%:127.0.0.1:%REMOTE_PORT% %SSH_USER%@%SSH_HOST% -N

echo SSH tunnel closed.
pause