import sys
import random

if len(sys.argv) != 3:
	print('Argument missing.\n')
	sys.exit()

file_name = sys.argv[1]

try:
	question_file = open(file_name, 'r')
except:
	print('File name doesn\'t exist.\n')
	sys.exit()

try:
	number_of_questions = int(sys.argv[2])
except:
	print('Number of questions should be integer.\n')
	sys.exit()

data = [x.strip() for x in question_file.read().split('||')]

heading = data.pop(0)

questions = {}



for q in data:
	question = [x.strip() for x in q.split('|')]
	questions[question[0]] = question[1:]

for sl in range(1, number_of_questions + 1):
	list_of_questions = list(questions.items())
	random.shuffle(list_of_questions)
	question_paper = heading
	
	for q_no, (question, option) in enumerate(list_of_questions):
		mcq = f'''
{q_no + 1}. {question}
   '''
		
		random.shuffle(option)
		opt = []
		for i, op in enumerate(option):
			make_option = f'{i + 1}. {op}'
			opt.append(make_option)
		
		question_paper += mcq + ', '.join(opt)
		
	print(f'Creating question {sl}...')
	
	new_question = open(f'{sys.argv[1][:-4]}{sl}.txt', 'w')
	new_question.write(question_paper)
	new_question.close()
	print('Succeeded.')

print(f'New questions {sys.argv[2]}.')
	
