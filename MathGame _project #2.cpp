// MathGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
using namespace std;
enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };
struct stQuestion
{
	short Number1 = 0;
	short Number2 = 0;
	enQuestionsLevel QuestionsLevel;
	enOperationType OperationType;
	int CorrectAnswers = 0;
	int PlayerAnswers = 0;
	bool AnswersResult = false;
};
struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions = 0;
	enQuestionsLevel QuestionsLevel;
	enOperationType OperationType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool isPass = false;
};
int Random(int From, int To)
{
	return rand() % (To - From + 1) + From;
}
short ReadHowManyQuestions()
{
	short ManyQuestions = 1;
	do
	{
		cout << "How Many Questions Do You want to answer ? :";
		cin >> ManyQuestions;

	} while (ManyQuestions < 0 || ManyQuestions > 10);

	return ManyQuestions;
}
enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionsLevel=0;
	do
	{
		cout << "Enter Qution Level [1] Easy , [2] Med , [3] Hard , [4] Mix ? ";
		cin >> QuestionsLevel;

	} while (QuestionsLevel < 1 || QuestionsLevel > 4);

	return (enQuestionsLevel)QuestionsLevel;
}
enOperationType ReadOperationType()
{
	short OperationType =0;
	do
	{
		cout << "Enter Operation Type  [1] Add , [2] Sub , [3] mul , [4] Div , [5] Max ? ";
		cin >> OperationType;

	} while (OperationType < 1 || OperationType > 5);

	return (enOperationType)OperationType;
}
int ReadAnswersPlayer()
{
	int AnswersPlayer1 = 1;
	cin >> AnswersPlayer1;
	return AnswersPlayer1;
}
enOperationType GetRandomOperationType()
{
	return (enOperationType)Random(1, 4);
}
int SimpleCalculator(int numbre1,int number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add :return numbre1 + number2;
	case enOperationType::Sub :return numbre1 - number2;
	case enOperationType::Mult:return numbre1 * number2;
	case enOperationType::Div :return numbre1 / number2;
	default :
		return numbre1 + number2;
	}
}
stQuestion GenerateQuestion(enQuestionsLevel  QuestionLevel, enOperationType  OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::Mix)
	{
		QuestionLevel = (enQuestionsLevel)Random(1, 3);
	}

	if (OpType == enOperationType::MixOp)
	{
		OpType = GetRandomOperationType();
	}

	Question.OperationType = OpType;
	
	switch (QuestionLevel)
	{
	case enQuestionsLevel::EasyLevel:
		Question.Number1 = Random(1,9);
		Question.Number2 = Random(1,9);
		Question.CorrectAnswers = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionsLevel = QuestionLevel;
		return Question;

	case enQuestionsLevel::MedLevel:
		Question.Number1 = Random(10,49);
		Question.Number2 = Random(10, 49);
		Question.CorrectAnswers = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionsLevel = QuestionLevel;
		return Question;
	
	case enQuestionsLevel::HardLevel:
		Question.Number1 = Random(50,100);
		Question.Number2 = Random(50, 100);
		Question.CorrectAnswers = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionsLevel = QuestionLevel;
		return Question;
	}

}
void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OperationType);
	}
}
string GetOpTypeSymble(enOperationType OpType)
{

	switch (OpType)
	{
	case enOperationType::Add : return "+";
	case enOperationType::Sub : return "-";
	case enOperationType::Mult: return "x";
	case enOperationType::Div : return "/";
	default:
		return "Mix";
	}
}
void RestScreen()
{
	system("cls");
	system("color 0F");
}
void PrintTheQuestion(stQuizz Quizz, short NumberOfQuestions)
{
	cout << "\n";
	cout << "Questions [" << NumberOfQuestions + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.QuestionList[NumberOfQuestions].Number1 << endl;
	cout << GetOpTypeSymble(Quizz.QuestionList[NumberOfQuestions].OperationType) << endl;
	cout << Quizz.QuestionList[NumberOfQuestions].Number2 << endl;
	cout << "__________________________________\n";
}
void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}

}
void CorrectTheQuestionAnswer(stQuizz& Quizz , short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].CorrectAnswers != Quizz.QuestionList[QuestionNumber].PlayerAnswers)
	{
		Quizz.QuestionList[QuestionNumber].AnswersResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Woring Anwer :-( \n";
		cout << "The Right Answers is "<< Quizz.QuestionList[QuestionNumber].CorrectAnswers;
		cout << "\n";

	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswersResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answers :-) \n";
		cout << "\n";
	}
	cout << endl;
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswersResult);
}
void AskAndCorrectQuestionListAnswers(stQuizz& Quizz )
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswers = ReadAnswersPlayer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);

	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}
string GetFinalResultText(bool Pass)
{
	if (Pass)
	    return "Pass :-)";
	else
		return "Fail :-(";

}
string GetQuestionsLevelText(enQuestionsLevel QuestionsLevel)
{
	switch (QuestionsLevel)
	{
	case enQuestionsLevel::EasyLevel:return "Easy";
	case enQuestionsLevel::MedLevel :return "Med";
	case enQuestionsLevel::HardLevel:return "Hard";
	default :
		return "Mix";
	}
}
void PrintQuizzResult(stQuizz Quizz)
{
	cout << "\n";
	cout << "________________________________________\n\n";
	cout << "Final Result is "<< GetFinalResultText(Quizz.isPass);
	cout << "\n________________________________________\n\n";

	cout << " Number of Questions : " << Quizz.NumberOfQuestions << endl;
	cout << " Questions Level    : " << GetQuestionsLevelText(Quizz.QuestionsLevel) << endl;
	cout << " OpType             : " << GetOpTypeSymble(Quizz.OperationType) << endl;
	cout << " Number Of Right Answers : " << Quizz.NumberOfRightAnswers << endl;
	cout << " Number Of Wrong Answers : " << Quizz.NumberOfWrongAnswers << endl;
	cout << "\n______________________________" << endl;

}
void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OperationType = ReadOperationType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResult(Quizz);
}
void StartGame()
{
	char PlayAgain = 'y';
	do
	{
		RestScreen();
		PlayMathGame();
		cout << "Do you to play again ? Y/N?";
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}

