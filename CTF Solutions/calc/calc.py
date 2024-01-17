import requests
import math

s = requests.Session()
r = s.get('http://ctf.hackucf.org:4000/calc/calc.php')


# print(r.text)

expression = r.text.split('<expression>')[1]
expression = expression.split('</expression>')[0]
expression = expression.split('<br/>')
# print(expression)

answer = int(expression[0])
for i in range(2, len(expression), 2):
    if (expression[i-1] == '-'):
        answer -= int(expression[i])
    elif (expression[i-1] == '+'):
        answer += int(expression[i])
    elif (expression[i-1] == '*'):
        answer *= int(expression[i])
        answer = math.floor(answer)
    else:
        answer /= int(expression[i])
        answer = math.floor(answer)
# print(answer)

post = s.post('http://ctf.hackucf.org:4000/calc/calc.php', data={'answer': answer}, headers = {'User-Agent': 'Mozilla/5.0'})

print(post.text)

#flag{you_should_have_solved_this_in_ruby}