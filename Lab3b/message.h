#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <windows.h>
#include <algorithm>
#include <QString>

#include "User.h"
#include "ui_mainwindow.h"

/// <summary>
/// Enam to store the type of the message
/// </summary>
enum class MESSAGE_TYPES {
    NEW_MESSAGE,
    REPLY_MESSAGE,
    REPOST_MESSAGE
};

/// <summary>
/// The class stores information about the message
/// </summary>
class Message {
public:
    Message(QTextBrowser *textBrowser, QString text, User* sender, std::list <QString> topics, std::vector <User> linksToOtherUsers, MESSAGE_TYPES type, Message* advanceNotice = nullptr);

    /// <summary>
    /// Method prints sms
    /// </summary>
    void OutMessage();

    /// <summary>
    /// Adds a user to the general list
    /// </summary>
    void AddUsers(std::vector <User> additionalUsers);

    /// <summary>
    /// The method is used to set the type of the message
    /// </summary>
    void SetType(MESSAGE_TYPES type);

    /// <summary>
    /// Used when displaying messages on the screen
    /// </summary>
    /// <returns>
    /// Returns a list of topics for this SMS
    /// </returns>
    inline std::list <QString> GetTopics() { return m_Topics; }

    /// <summary>
    /// Used when displaying messages on the screen
    /// </summary>
    /// <returns>
    /// Returns a link to the replied message
    /// </returns>
    inline Message *GetAdvanceNotice() { return m_AdvanceNotice; }

    /// <summary>
    /// Used when displaying messages on the screen
    /// </summary>
    /// <returns>
    /// Returns the rating of this SMS
    /// </returns>
    inline int GetRating() { return m_Rating; }

    /// <returns>
    /// Returns the type of this SMS
    /// </returns>
    inline MESSAGE_TYPES GetType() { return m_Type; }
    //    inline QTextBrowser *GetTextBrowser() { return m_TextBrowser; }
    //    inline QString GetText() { return m_Text; }
    //    inline std::vector <user> GetLinksToOtherUsers() { return m_LinksToOtherUsers; }

    /// <summary>
    /// Creates a new message
    /// </summary>
    /// <returns>
    /// Returns the created message
    /// </returns>
    static Message CreateMessage(QTextBrowser *textBrowser, QString text, User* sender, std::list <QString> topics, std::vector <User> linksToOtherUsers);

    /// <summary>
    /// Creates a new message as a reply to another SMS
    /// </summary>
    /// <returns>
    /// Returns the created message
    /// </returns>
    static Message CreateReply(Message* MSG, QString text, User* sender, std::list <QString> topics, std::vector <User> linksToOtherUsers);

    /// <summary>
    /// Creates a copy of the forwarded message
    /// </summary>
    /// <returns>
    /// Returns the created message
    /// </returns>
    static Message CreateRepost(Message MSG, std::vector <User> additionalUsers);

    /// <summary>
    /// Increases or decreases the rating of the message depending on the accepted boolean parameter
    /// </summary>
    static void EvaluateTheMessage(Message& MSG, bool mark);

private:
    QString m_Text;
    User* m_Sender;
    std::list <QString> m_Topics;
    std::vector <User> m_LinksToOtherUsers;
    Message *m_AdvanceNotice;
    int m_Rating = 0;
    int m_Hour, m_Minutes, m_Second;
    MESSAGE_TYPES m_Type;
    QTextBrowser *m_TextBrowser;

    inline QString GetTime() {
        return (QString::number(m_Hour) + ":" + QString::number(m_Minutes) + ":" + QString::number(m_Second));
    }
    void IncreaseRating();
    void DowngradeRating();
};


