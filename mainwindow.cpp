#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <iostream>


// Предположим, что у нас есть массив вопросов и ответов
QStringList questions = {
    "Вопрос 1: Кто подарил Гарри сову?",
    "Вопрос 2: Какая сердцевина волшебной палочки Гермионы?",
    "Вопрос 3: Какое заклинание заставляет объект левитировать?",
    "Вопрос 4: Какое украшение принадлежало Кондиде Когтевран?",
    "Вопрос 5: Как назывался змей из тайной комнаты?",
    "Вопрос 6: Как зовут старшую двоюродную сестру Сириуса Блэка?",
    "Вопрос 7: Кто был участником Кубка Огня от школы Шармбатон ?",
    "Вопрос 8: Какое было прозвище было у профессора Люпина?",
    "Вопрос 9: Что преподавала Долорес Амбридж",
    "Вопрос 10: Как звали призрака жившего в туалете?",
    "Вопрос 11: Из-за какого растения Невил потерял сознание?",
    "Вопрос 12: Какой язык знал Том Реддл?",
    "Вопрос 13: Как звали самого старшего брата Рона?",
    "Вопрос 14: Какой предмет преподавала Профессор Трелони в Хогвартсе?",
    "Вопрос 15: Любимое заклинение Гарри Поттера?",
    "Вопрос 16: Какой предмет преподавал Слизнорт в Хогвартсе?",
    "Вопрос 17: Какое заклинание используется для обезоруживания противника?",
    "Вопрос 18: Как справиться с дементором?",
    "Вопрос 19: На ком женился Гарри Поттер?",
    "Вопрос 20: кто убил Беллатрису Лестрейндж?"
};

QList<QStringList> answers = {
    {"Дамблдор", "Хагрид", "Молли Уизли"},//1
    {"Жила дракона", "Перо феникса", "Волос единорога"},//2
    {"Вингардиум ЛЕвиосса", "Вингардиум ЛевиОсса", "Вингардиум ЛевиоссА"},//3
    {"Чаша", "Диадема", "Медальон"},//4
    {"Горыныч", "Титанобоа", "Василиск"},//5
    {"Беллатриса", "Нарцисса", "Андромеда"},//6
    {"Габриель", "Флер де Лакур", "Олимпия Максим"},//7
    {"Сохатый", "Бродяга", "Лунатик"},//8
    {"Невидимость", "Защиту от темных искусств", "Заклинания"},//9
    {"Кровавый Барон", "Плакса Миртл", "Почти Безголовый Ник"},//10
    {"Мимбулус Мимблетония", "Мандрагора", "Гремучая Ива"},//11
    {"Язык троллей", "Гоблинский", "Парселтанг"},//12
    {"Чарли", "Билл", "Перси"},//13
    {"Прорицание", "Нумерология", "Трансфигурация"},//14
    {"Экспекто Патронум", "Империо", "Экспеллириармус"},//15
    {"Зельеварение", "Травология", "Защита от темных искусств"},//16
    {"Экспеллиармус", "Импедимента", "Экспекто патронум"},//17
    {"Импедимента", "Экспекто патронум", "Ридикулус"},//18
    {"Гермиона", "Полумна", "Джини"},//19
    {"Нимфадора Тонкс", "Гермиона Грейнджер", "Молли Уизли"}//20
};

int corrects[] = {
    1,//1
    0,//2
    1,//3
    1,//4
    2,//5
    0,//6
    1,//7
    2,//8
    1,//9
    1,//10
    1,//11
    2,//12
    1,//13
    0,//14
    2,//15
    0,//16
    0,//17
    1,//18
    2,//19
    2 //20
};



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentQuestionIndex(0),
    correctAnswersCount(0)
{
    ui->setupUi(this);

    // Устанавливаем фоновое изображение
    QPixmap bkgnd(":/images/background.jpg");
    bkgnd = bkgnd.scaled(this->size());
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    this->setMaximumSize(this->size());

    // Подключаем сигналы к слотам
    connect(ui->nextButton, &QPushButton::clicked, this, &MainWindow::onNextClicked);
    connect(ui->finishButton, &QPushButton::clicked, this, &MainWindow::onFinishClicked);

    // Загружаем первый вопрос
    loadQuestion(currentQuestionIndex);

    // Путь к файлу стилей
    QString stylePath = ":/style/radioStyle.qss";

    // Загрузка файла стилей
    QFile styleFile(stylePath);
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString style = styleFile.readAll();
        ui->answer1RadioButton->setStyleSheet(style);
        ui->answer2RadioButton->setStyleSheet(style);
        ui->answer3RadioButton->setStyleSheet(style);
        styleFile.close();
    }

    // Путь к файлу стилей
    QString stylePath2 = ":/style/buttonStyle.qss";

    // Загрузка файла стилей
    QFile styleFile2(stylePath2);
    if (styleFile2.open(QFile::ReadOnly | QFile::Text)) {
        QString style = styleFile2.readAll();
        ui->nextButton->setStyleSheet(style);
        ui->finishButton->setStyleSheet(style);
        styleFile2.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadQuestion(int index)
{
    // Устанавливаем вопрос
    ui->questionLabel->setText(questions[index]);

    // Устанавливаем варианты ответов
    ui->answer1RadioButton->setText(answers[index][0]);
    ui->answer2RadioButton->setText(answers[index][1]);
    ui->answer3RadioButton->setText(answers[index][2]);

    // Очищаем выбор пользователя
    ui->answer1RadioButton->setAutoExclusive(false);
    ui->answer2RadioButton->setAutoExclusive(false);
    ui->answer3RadioButton->setAutoExclusive(false);
    ui->answer1RadioButton->setChecked(false);
    ui->answer2RadioButton->setChecked(false);
    ui->answer3RadioButton->setChecked(false);
    ui->answer1RadioButton->setAutoExclusive(true);
    ui->answer2RadioButton->setAutoExclusive(true);
    ui->answer3RadioButton->setAutoExclusive(true);

    // Если это последний вопрос, скрываем кнопку "Далее" и показываем "Завершить тест"
    if (index == questions.size() - 1) {
        ui->nextButton->setVisible(false);
        ui->finishButton->setVisible(true);
    }
    else {
        ui->nextButton->setVisible(true);
        ui->finishButton->setVisible(false);
    }
}

void MainWindow::onNextClicked()
{
    // Проверяем правильность ответа
    if (ui->answer1RadioButton->isChecked()&&corrects[currentQuestionIndex]==0) {
        correctAnswersCount++;
    }else if (ui->answer2RadioButton->isChecked()&&corrects[currentQuestionIndex]==1) {
        correctAnswersCount++;
    }else if (ui->answer3RadioButton->isChecked()&&corrects[currentQuestionIndex]==2) {
        correctAnswersCount++;
    }

    // Загружаем следующий вопрос
    currentQuestionIndex++;
    loadQuestion(currentQuestionIndex);
}

void MainWindow::onFinishClicked()
{
    // Проверяем правильность ответа на последний вопрос
    if (ui->answer1RadioButton->isChecked()&&corrects[currentQuestionIndex]==0) {
        correctAnswersCount++;
    }else if (ui->answer2RadioButton->isChecked()&&corrects[currentQuestionIndex]==1) {
        correctAnswersCount++;
    }else if (ui->answer3RadioButton->isChecked()&&corrects[currentQuestionIndex]==2) {
        correctAnswersCount++;
    }

    // Выводим результаты
    QString resultMessage = QString("Вы ответили правильно на %1 из %2 вопросов.")
        .arg(correctAnswersCount)
        .arg(currentQuestionIndex + 1);

    QMessageBox::information(this, "Результаты", resultMessage);

    currentQuestionIndex=0;
    correctAnswersCount=0;
    loadQuestion(currentQuestionIndex);
}
