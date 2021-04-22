#include <iostream>
#include <string>

using namespace std;

//Model 模型类 Student
class Student {
public:
	Student() {};
	~Student() {};

	string getRollNo();
	void setRollNo(string rollNo);
	string getName();
	void setName(string name);

private:
	string rollno;
	string name;
};

string Student::getRollNo() {
	return rollno;
}

void Student::setRollNo(string rollNo) {
	this->rollno = rollNo;
}

string Student::getName() {
	return name;
}

void Student::setName(string name) {
	this->name = name;
}

// 视图类 StudentView
class StudentView {
public:
	StudentView() {};
	~StudentView() {};

	void printStudentDetails(string studentname, string studentrollno);
};

void StudentView::printStudentDetails(string studentname, string studentrollno) {
	cout << "Student: " << endl 
		<< "Name: " << studentname << endl
		<< "roll No: " << studentrollno << endl;
}

//controller控制器类 StudentController
class StudentController {
public:
	StudentController(Student model, StudentView view);
	~StudentController() {};

	void setStudentName(string name);
	string getStudentName();
	void setStudentRollNo(string rollno);
	string getStudentName();
	void updateView();
private:
	Student model;
	StudentView view;
};


StudentController::StudentController(Student model, StudentView) {
	this->model = model;
	this->view = view;
}

void StudentController::setStudentName(string name) {
	this->model.setName(name);
}

string StudentController::getStudentName() {
	return this->model.getName();
}

void StudentController::setStudentRollNo(string rollno) {
	this->model.setRollNo(rollno);
}

string StudentController::getStudentRollNo() {
	return this->model.getRollNo();
}

void StudentController::updateView() {
	this->view.printStudentDetails(this->model.getName(), this->model.getRollNo());
}

int main() {
	Student model;
	model.setName("Robert");
	model.setRollNo("10");
	StudentView view;
	StudentController controller(model, view);

	controller.updateView();
	controller.setStudentName("John");
	controller.updateView();

	system("pause");
	return 0;
}