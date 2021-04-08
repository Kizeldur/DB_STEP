#include "mainwindow.h"
#include "ui_mainwindow.h"



DataBase db("C:\\Users\\Admin\\Desktop\\DB_STEP.sqlite");
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Автозагрузка
    db.Open_2(this->ui);
    }

MainWindow::~MainWindow()
{
    delete ui;
    // Автосохранение
    db.Close();
}


//очистить поля
 void MainWindow::on_Button_Insert_Student_clicked()
{
  QString tableName = "students";
  QString valueName = "faculty";
  QString firstname = ui->Input_Name->text();
  QString lastname = ui->Input_LastName->text();
  QString patronym = ui->Input_Patronym->text();
  QString birthday = ui->Input_Birthday->text();
  QString faculty = ui->Input_Faculty->text();

  ui->statusbar->showMessage("Insert");
  bool flagExecuted = db.Insert_2(ui, tableName, firstname, lastname, patronym, birthday, faculty, valueName);
  auto str = GiveMeInsertMessage(flagExecuted);
  ui->statusbar->showMessage(str);
    db.Insert(tableName, firstname, lastname, patronym, birthday, faculty, valueName);
  // показать сообщение
  ClearUIInput(ui);

}


 // очистить поля после апдейтпа
 void MainWindow::on_Button_Edit_Student_clicked()
{
  QString tableName = "students";
  QString valueName = "Faculty";
  bool flagExecuted;

  QString name = ui->Input_Search_Name->text();
  QString lastName = ui->Input_Search_LastName->text();
  QString patronym = ui->Input_Search_Patronym->text();
  QString dateOfBirth = ui->Input_Search_Birthday->text();
  QString faculty = ui->Input_Search_Faculty->text();
  int id = db.GiveMeId_2(ui, tableName, lastName, "0");
  //db.Edit(tableName, id,  firstname, lastname, patronym, birthday, faculty, valueName);
  flagExecuted = db.Edit_2(ui, tableName, id, name, lastName, patronym, dateOfBirth, faculty, valueName);
  //ui->statusbar->showMessage(GiveMeEditMessage(flagExecuted));
  ClearUIEdit(ui);
}


  void MainWindow::on_Button_Delete_clicked(){
      //int id = ui->Input_Search_Id->text();
      QString tableName = "students";
      QString lastName = ui->Input_Search_LastName->text();
      int id = db.GiveMeId_2(ui, tableName, lastName, "0");
// дописать функцию giveMeProperTableName
     bool flagExecuted = db.Delete_2(ui, tableName, id);
     //ui->statusbar->showMessage(QString::number(id));
     ui->statusbar->showMessage(GiveMeDeleteMessage(flagExecuted));
     ClearUIEdit(ui);
  }



// Подумать, куда сохранять ИД
  void MainWindow::on_Button_Search_clicked(){
      QString tableName = "students";
      QString lastName = ui->Input_Search->text();

      int id = db.GiveMeId_2(ui, tableName, lastName, "0");
      ui->statusbar->showMessage("123 " + QString::number(id));
      PersonTemplate person = db.Search_2(ui, tableName, id);
      bool flagIsActive = person.isActive;
      if(flagIsActive){
      ui->Input_Search_Name->setText(person.name);
      ui->Input_Search_LastName->setText(person.lastName);
      ui->Input_Search_Patronym->setText(person.patronym);
      ui->Input_Search_Birthday->setText(person.dateOfBirth);
      ui->Input_Search_Faculty->setText(person.otherData);
      }
      ui->statusbar->showMessage(GiveMeDeleteMessage(flagIsActive));
      ClearUISearch(ui);
  }

//очищение данных на экране
 /*
void MainWindow::on_Button_Clear_clicked()
 {
     ui->Input_Search->clear();

 }
*/
//Button_Find_onclick
// void MainWindow::on_button_find_clicked()
//{
//  QString fistname, lastname, patronym, dateOfBirth, otherdata
//    auto key = ui->input_Key->text();
//      auto person = db.QueryPerson(key);
//      firstname = person.firstname;
//      lastname = person.lastname;
//      patronym = person.patronym;
//      dateofbirth = person.dateofbirth;
//      if(otherdata заполнена чем-то ){
//             Функция, записывающая в ui-таблицу данные
//}

//
//
//
//}

void MainWindow::on_Button_Export_S_clicked()
{
    QString Input_Address_S;
    QString tableName = "students";
    QFile File_Step (Input_Address_S);

    if(!File_Step.open(QFile::Append | QFile::Text)){
        QMessageBox ::information(this,"ERROR","No path corect");
        return;
    }

    QTextStream stream(&File_Step);
    for (int i = 0; i < 7; i++) {
      PersonTemplate person = db.Search_2(ui, tableName, i);
      stream  << person.name << ";"
              << person.lastName<< ";"
              << ui->person.patronym<< ";"
              << ui->person.dateOfBirth<< ";"
              << ui->person.otherData->text() + "\n";
    }

    File_Step.flush();
    File_Step.close();
}
void MainWindow::on_Button_Export_E_clicked()
{
  QString Input_Address_S;
  QString tableName = "employee";
  QFile File_Step (Input_Address_S);

  if(!File_Step.open(QFile::Append | QFile::Text)){
      QMessageBox ::information(this,"ERROR","No path corect");
      return;
  }

  QTextStream stream(&File_Step);
  for (int i = 0; i < 7; i++) {
    PersonTemplate person = db.Search_2(ui, tableName, i);
    stream  << person.name << ";"
            << person.lastName<< ";"
            << ui->person.patronym<< ";"
            << ui->person.dateOfBirth<< ";"
            << ui->person.otherData->text() + "\n";
  }

  File_Step.flush();
  File_Step.close();
}

void MainWindow::on_Button_Export_A_clicked()
{
  QString Input_Address_S;
  QString tableName = "enrollee";
  QFile File_Step (Input_Address_S);

  if(!File_Step.open(QFile::Append | QFile::Text)){
      QMessageBox ::information(this,"ERROR","No path corect");
      return;
  }

  QTextStream stream(&File_Step);
  for (int i = 0; i < 7; i++) {
    PersonTemplate person = db.Search_2(ui, tableName, i);
    stream  << person.name << ";"
            << person.lastName<< ";"
            << ui->person.patronym<< ";"
            << ui->person.dateOfBirth<< ";\n";
  }

  File_Step.flush();
  File_Step.close();
}

void MainWindow::on_Button_Import_clicked()
{
QString Input_Address_S;
QFile File_Step ("C:\\Users\\Admin\\Desktop\\DB_STEP-master\\File_Step.csv");

if (!File_Step.open(QFile::ReadOnly | QFile::Text)){
          QMessageBox ::information(this,"ERROR","No path corecct");
          return;
      }
      QTextStream stream(&File_Step);
      while(!stream.atEnd())
        {
          QString temp = stream.readLine();
          QRegExp tagExp(";");
          QStringList firstList = temp.split(tagExp);
          PersonTemplate p(firstList[1], firstList[0], firstList[2], firstList[3],1, firstList[4],-1);
        	if(ui->radioButton_Student->isChecked()){
            db.Insert_2(ui, "students", p.name, p.lastName, p.patronym, p.dateOfBirth, p.otherData, "faculty");
			    } else
			    if(ui->radioButton_Employee->isChecked()){
            db.Insert_2(ui, "employee", p.name, p.lastName, p.patronym, p.dateOfBirth, p.otherData, "position");
			    } else
          if(ui->radioButton_Enrollee->isChecked()){
            db.Insert_2(ui, "enrollee", p.name, p.lastName, p.patronym, p.dateOfBirth, p.otherData, "0");
			    }
        }

        File_Step.flush();
        File_Step.close();

}
