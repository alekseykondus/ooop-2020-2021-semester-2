#include "message.h"
#include "ui_mainwindow.h"

Message::Message(QTextBrowser *textBrowser, QString text, User* sender, std::list <QString> topics, std::vector <User> linksToOtherUsers, MESSAGE_TYPES type, Message* advanceNotice)
    : m_Text(text),
      m_Sender(sender),
      m_Topics(topics),
      m_LinksToOtherUsers(linksToOtherUsers),
      m_Type(type),
      m_AdvanceNotice(advanceNotice),
      m_TextBrowser(textBrowser) {

    SYSTEMTIME st;
    GetSystemTime(&st);
    m_Hour = st.wHour + 3;
    m_Minutes = st.wMinute;
    m_Second = st.wSecond;
}

void Message::OutMessage() {
    m_TextBrowser->insertPlainText(this->GetTime()+"\n");
    m_TextBrowser->insertPlainText("user: " + m_Sender->GetName()+"\n");
    m_TextBrowser->insertPlainText("topics: ");
    for (QString str : m_Topics)
        m_TextBrowser->insertPlainText(str+";  ");
    m_TextBrowser->insertPlainText("\n");
    m_TextBrowser->insertPlainText("Text: " + m_Text+"\n");
    m_TextBrowser->insertPlainText("rating: " + QString::number(m_Rating) +"\n\n");

/*    std::cout << this->GetTime() << std::endl
              << "user: " << m_Sender->GetName() << std::endl
              << "topics: ";
    for (std::string str : m_Topics)
        std::cout << str << ";  ";
    std::cout << std::endl
              << "Text: " << m_Text << std::endl
              << "rating: " << m_Rating
              << std::endl << std::endl;
              */
}

void Message::AddUsers(std::vector <User> additionalUsers) {
    for (std::size_t i = 0; i < additionalUsers.size(); i++)
        m_LinksToOtherUsers.push_back(additionalUsers[i]);
}

void Message::SetType(MESSAGE_TYPES type) {
    m_Type = type;
}

void Message::IncreaseRating() {
    m_Rating += 1;
}
void Message::DowngradeRating() {
    m_Rating--;
}

Message Message::CreateMessage(QTextBrowser *textBrowser, QString text, User* sender, std::list <QString> topics, std::vector <User> linksToOtherUsers) {
    Message MSG{textBrowser, text, sender, topics, linksToOtherUsers, MESSAGE_TYPES::NEW_MESSAGE };

    if (textBrowser) {
        MSG.m_TextBrowser->setFontWeight( QFont::DemiBold);
        MSG.m_TextBrowser->setTextColor( QColor( Qt::yellow ) );
        MSG.m_TextBrowser->insertPlainText(QString("New message:\n"));
        MSG.m_TextBrowser->setFontWeight( QFont::Normal);
        MSG.m_TextBrowser->setTextColor( QColor( Qt::black ) );
        MSG.OutMessage();
    }

    return MSG;
}
Message Message::CreateReply(Message* MSG, QString text, User* sender, std::list <QString> topics, std::vector <User> linksToOtherUsers) {
    Message MSG_reply{MSG->m_TextBrowser, text, sender, topics, linksToOtherUsers, MESSAGE_TYPES::REPLY_MESSAGE, MSG };

    if (MSG->m_TextBrowser) {
        MSG->m_TextBrowser->setFontWeight( QFont::DemiBold);
        MSG->m_TextBrowser->setTextColor( QColor( Qt::darkMagenta ) );
        MSG->m_TextBrowser->insertPlainText(QString("reply message:\n"));
        MSG->m_TextBrowser->setFontWeight( QFont::Normal);
        MSG->m_TextBrowser->setTextColor( QColor( Qt::black ) );
        MSG->OutMessage();

        MSG->m_TextBrowser->setFontWeight( QFont::DemiBold);
        MSG->m_TextBrowser->setTextColor( QColor( Qt::green ) );
        MSG->m_TextBrowser->insertPlainText(QString("answer:\n"));
        MSG->m_TextBrowser->setFontWeight( QFont::Normal);
        MSG->m_TextBrowser->setTextColor( QColor(  Qt::black ) );
        MSG_reply.OutMessage();
    }

    return MSG_reply;
}

Message Message::CreateRepost(Message MSG, std::vector <User> additionalUsers) {
    Message MSG_repost = MSG;
    MSG_repost.AddUsers(additionalUsers);
    MSG_repost.SetType(MESSAGE_TYPES::REPOST_MESSAGE);

    if (MSG_repost.m_TextBrowser) {
        MSG_repost.m_TextBrowser->setFontWeight( QFont::DemiBold);
        MSG_repost.m_TextBrowser->setTextColor( QColor( Qt::red ) );
        MSG_repost.m_TextBrowser->insertPlainText(QString("forwarded message:\n"));
        MSG_repost.m_TextBrowser->setFontWeight( QFont::Normal);
        MSG_repost.m_TextBrowser->setTextColor( QColor(  Qt::black ) );
        MSG_repost.OutMessage();
    }

    return MSG_repost;
}

void Message::EvaluateTheMessage(Message& MSG, bool mark) {
    if (mark)
        MSG.IncreaseRating();
    else
        MSG.DowngradeRating();
}
