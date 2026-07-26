yes | cp -rf /home/ghunter/GameServer/GameServer  /home/ghunter/build/GameServer1
yes | cp -rf /home/ghunter/GameServer/GameServer  /home/ghunter/build/GameServer2
yes | cp -rf /home/ghunter/GameServer/GameServer  /home/ghunter/build/GameServer3
yes | cp -rf /home/ghunter/GameServer/GameServer  /home/ghunter/build/GameServer4
yes | cp -rf /home/ghunter/LoginServer/LoginServer  /home/ghunter/build/Login
yes | cp -rf /home/ghunter/Helper/Helper            /home/ghunter/build/Helper
yes | cp -rf /home/ghunter/SubHelper/SubHelper      /home/ghunter/build/SubHelper
yes | cp -rf /home/ghunter/Connector/Connector      /home/ghunter/build/Connector
yes | cp -rf /home/ghunter/Messenger/Messenger      /home/ghunter/build/Messenger
sleep 5
find /home/ghunter/GameServer -type f -name "*.dwo" -exec cp -f {} /home/ghunter/build/dwo/ \;
sleep 3
echo "renaming files"
mv /home/ghunter/build/GameServer1/GameServer /home/ghunter/build/GameServer1/GameServer1
mv /home/ghunter/build/GameServer2/GameServer /home/ghunter/build/GameServer2/GameServer2
mv /home/ghunter/build/GameServer3/GameServer /home/ghunter/build/GameServer3/GameServer3
mv /home/ghunter/build/GameServer4/GameServer /home/ghunter/build/GameServer4/GameServer4
