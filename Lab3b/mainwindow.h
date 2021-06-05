#pragma once

#include <QMainWindow>
#include "message.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    /// <summary>
    /// Slot by pressing the Imitation button on UI
    /// </summary>
    void on_pushButtonImitation_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Message> message_vector;
    std::list <QString> favorite_topics;
    std::list <User> friends;

    /// <summary>
    /// A method that implements to model a social network
    /// </summary>
    void NetworkSimulator(QTextBrowser *textBrowser, size_t number, float second);

    /// <summary>
    /// The method calculates the design capacity
    /// </summary>
    /// <returns>
    /// Returns a sorted vector of elements by the calculated performance
    /// </returns>
    std::vector<Message> MessageSelectionAlgorithm(User u, std::vector<Message> message_vector);
};

/// <summary>
/// Creates a message with a random type and random content
/// </summary>
void CreateRandomMessage(QTextBrowser *textBrowser, std::vector<Message>& message_vector, User& u1, User& u2, User& u3, User& u4, int r);
