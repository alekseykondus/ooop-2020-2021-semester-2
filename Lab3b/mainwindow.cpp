#include <ctime>
#include <random>
#include <thread>
#include <mutex>
#include "mainwindow.h"

std::random_device rd;
std::mt19937 mersenne(rd());
std::mutex mu;

std::vector<Message> MainWindow::MessageSelectionAlgorithm(User u, std::vector<Message> message_vector) {
    std::vector<std::pair<Message, int>> selected_messages;
    for (size_t i = 0; i < message_vector.size(); i++) {
        int novelty_factor = i + 1; //коефіцієнт новизни повідомлення (так як у векторі елементи розташовані
        //у порядку їх створення (у тому числі і за часом створення), то коефіціентом може будет номер елемента у векторі)
        int coefficient_rating = message_vector[i].GetRating() + 100; //коефіцієнт рейтингу

        int topic_rate = 1; //коефіцієнт співпадіння тем
        for (QString str1 : u.GetFavoriteTopics())
            for (QString str2 : message_vector[i].GetTopics())
                if (str1 == str2)
                    topic_rate++;

        int coefficient = novelty_factor * topic_rate * coefficient_rating;
        std::pair<Message, int> p(message_vector[i], coefficient);
        selected_messages.push_back(p);
    }
    std::sort(selected_messages.begin(), selected_messages.end(), [](std::pair<Message, int> p1, std::pair<Message, int> p2) { return (p2.second) < (p1.second); }); //сортуємо вектор по коефіцієнтам

    std::vector<Message> sorted_message_vector;
    for (std::pair<Message, int> element : selected_messages)
        sorted_message_vector.push_back(element.first);
    return sorted_message_vector; //повертаємо відсортований по коефіцієнтам вектор повідомлень
}

void CreateRandomMessage(QTextBrowser *textBrowser, std::vector<Message>& message_vector, User& u1, User& u2, User& u3, User& u4, int r) {
    switch (r) {
    case 1: //створюємо повідомлення
    {
        int r2 = mersenne() % 5;
        QString message_text;
        std::list <QString> message_text_topics;
        std::vector <User> message_text_links_to_other_users;
        switch (r2)
        {//чотири варіанти повідомлень:
        case 1:
        {
            message_text = "sms " + QString::number(mersenne() % 100);
            message_text_topics.push_back("topic " + QString::number(mersenne() % 7));
            message_text_topics.push_back("topic " + QString::number(mersenne() % 7 + 7));
            message_text_links_to_other_users.push_back(u1);
        }
        break;
        case 2:
        {
            message_text = "sms " + QString::number(mersenne() % 100);
            message_text_topics.push_back("topic " + QString::number(mersenne() % 12));
            message_text_topics.push_back("topic " + QString::number(mersenne() % 7 + 7));
            message_text_topics.push_back("topic " + QString::number(mersenne() % 18 + 7));
            message_text_links_to_other_users.push_back(u2);
        }
        break;
        case 3:
        {
            message_text = "sms " + QString::number(mersenne() % 100);
            message_text_topics.push_back("topic " + QString::number(mersenne() % 5));
            message_text_topics.push_back("topic " + QString::number(mersenne() % 8 + 7));
            message_text_topics.push_back("topic " + QString::number(mersenne() % 15 + 7));
            message_text_links_to_other_users.push_back(u3);
            message_text_links_to_other_users.push_back(u4);
        }
        break;
        case 4:
        {
            message_text = "sms " + QString::number(mersenne() % 100);
            message_text_topics.push_back("topic " + QString::number(mersenne() % 5));
            message_text_topics.push_back("topic " + QString::number(mersenne() % 8 + 7));
            message_text_topics.push_back("topic " + QString::number(mersenne() % 15 + 15));
            message_text_topics.push_back("topic " + QString::number(mersenne() % 25 + 15));
            message_text_topics.push_back("topic " + QString::number(mersenne() % 35 + 15));
            message_text_links_to_other_users.push_back(u2);
            message_text_links_to_other_users.push_back(u3);
            message_text_links_to_other_users.push_back(u4);
        }
        break;
        default:
            break;
        }
        mu.lock();
        message_vector.push_back(Message::CreateMessage(textBrowser, message_text, &u1, message_text_topics, message_text_links_to_other_users));
//        out_Message(message_vector.back());
        mu.unlock();
    }
    break;
    case 2://оцінюємо повідомлення
    {
        int r2 = mersenne() % message_vector.size();
        Message::EvaluateTheMessage(message_vector[r2], 1);
    }
    break;
    case 3://оцінюємо та репостимо повідомлення
    {
        int r2 = mersenne() % message_vector.size();
        Message::EvaluateTheMessage(message_vector[r2], 1);
        std::vector <User> additional_users;
        additional_users.push_back(u1);
        additional_users.push_back(u3);

        mu.lock();
        message_vector.push_back(Message::CreateRepost(message_vector[0], additional_users));
//        out_Message(message_vector.back());
        mu.unlock();
    }
    break;
    case 4://відповідаємо на повідомлення
    {
        int r2 = mersenne() % message_vector.size();
        QString message_text = "sms reply ";
        std::list <QString> message_text_topics;
        message_text_topics.push_back("topic 2");
        std::vector <User> message_text_links_to_other_users;
        message_text_links_to_other_users.push_back(u2);
        message_text_links_to_other_users.push_back(u3);
        message_text_links_to_other_users.push_back(u4);

        mu.lock();
        message_vector.push_back(Message::CreateReply(&message_vector[r2], message_text, &u4, message_text_topics, message_text_links_to_other_users));
//        out_Message(message_vector.back());
        mu.unlock();
    }
    break;
    default:
        break;
    }
}

void MainWindow::NetworkSimulator(QTextBrowser *textBrowser, size_t number, float second) {
    int start = clock();

    //чотири користувачі
    QString name = "Alex";
    favorite_topics.push_back("topic "+QString::number(mersenne() % 50));
    favorite_topics.push_back("topic "+QString::number(mersenne() % 50));
    favorite_topics.push_back("topic "+QString::number(mersenne() % 50));
    favorite_topics.push_back("topic "+QString::number(mersenne() % 50));
    User u1{ name, friends,favorite_topics }; //надсилає повідомлення

    name = "Petya";
    friends.clear();
    friends.push_back(u1);
    favorite_topics.clear();
    favorite_topics.push_back("topic "+QString::number(mersenne() % 50));
    favorite_topics.push_back("topic "+QString::number(mersenne() % 50));
    User u2{ name, friends,favorite_topics }; //оцінює повідомлення

    name = "Vanya";
    friends.clear();
    friends.push_back(u1);
    friends.push_back(u2);
    favorite_topics.clear();
    favorite_topics.push_back("topic "+QString::number(mersenne() % 50));
    favorite_topics.push_back("topic "+QString::number(mersenne() % 50));
    favorite_topics.push_back("topic "+QString::number(mersenne() % 50));
    favorite_topics.push_back("topic "+QString::number(mersenne() % 50));
    favorite_topics.push_back("topic "+QString::number(mersenne() % 50));
    User u3{ name, friends, favorite_topics }; //оцінює і пересилає повідомлення

    name = "John";
    friends.clear();
    friends.push_back(u1);
    friends.push_back(u2);
    friends.push_back(u3);
    favorite_topics.clear();
    favorite_topics.push_back("topic 1");
    User u4{ name, friends, favorite_topics }; //відповідає на повідомлення

    size_t time = 0;
    std::vector<std::thread> some_threads;

    for (size_t i = 0; i < number && time < second; i++) {
        int r = (message_vector.size() == 0) ? 1 : mersenne() % 5;

        some_threads.push_back(std::thread([&]() {CreateRandomMessage(textBrowser, message_vector, u1, u2, u3, u4, r); }));

        if (message_vector.size() == 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

        int end = clock(); // контролюємо час роботи
        time = (end - start) / CLOCKS_PER_SEC;
    }
    for (auto& thread : some_threads)
        thread.join();

    MessageSelectionAlgorithm(u1, message_vector);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonImitation_clicked()
{
    NetworkSimulator(ui->textBrowser, ui->numberOfSMS->text().toInt(), ui->simulationTime->text().toFloat());
}
