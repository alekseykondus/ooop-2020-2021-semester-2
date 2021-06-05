#include <random>
#include "mainwindow.h"

#define DOCTEST_CONFIG_IMPLEMENT
#ifdef DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

TEST_CASE("checking user") {
    std::list <QString> TEST_favorite_topics;
    std::list <User> TEST_friends;
    CHECK(TEST_favorite_topics.empty());
    CHECK(TEST_friends.empty());

    QString name = "Alex";
    TEST_favorite_topics.push_back("topic "+QString::number(rand() % 50));
    TEST_favorite_topics.push_back("topic "+QString::number(rand() % 50));
    TEST_favorite_topics.push_back("topic "+QString::number(rand() % 50));
    TEST_favorite_topics.push_back("topic "+QString::number(rand() % 50));
    User user1{ name, TEST_friends, TEST_favorite_topics };
    CHECK(TEST_favorite_topics.size() == 4);
    CHECK(user1.GetFavoriteTopics() == TEST_favorite_topics);
    CHECK(user1.GetName() == name);

    name = "Petya";
    TEST_friends.clear();
    TEST_favorite_topics.clear();
    TEST_friends.push_back(user1);
    TEST_favorite_topics.clear();
    TEST_friends.push_back(user1);
    TEST_favorite_topics.push_back("topic "+QString::number(rand() % 50));
    TEST_favorite_topics.push_back("topic "+QString::number(rand() % 50));
    User user2{ name, TEST_friends, TEST_favorite_topics };

    CHECK(TEST_favorite_topics.size() == 2);
    CHECK(user2.GetFavoriteTopics() == TEST_favorite_topics);
    CHECK(user2.GetName() == name);
}

TEST_CASE("checking message") {
    std::vector<Message> message_vector;
    std::list <QString> favorite_topics;
    std::list <User> friends;
    //чотири користувачі
    QString name = "Alex";
    favorite_topics.push_back("topic "+QString::number(rand() % 50));
    favorite_topics.push_back("topic "+QString::number(rand() % 50));
    favorite_topics.push_back("topic "+QString::number(rand() % 50));
    favorite_topics.push_back("topic "+QString::number(rand() % 50));
    User u1{ name, friends,favorite_topics }; //надсилає повідомлення

    name = "Petya";
    friends.clear();
    friends.push_back(u1);
    favorite_topics.clear();
    favorite_topics.push_back("topic "+QString::number(rand() % 50));
    favorite_topics.push_back("topic "+QString::number(rand() % 50));
    User u2{ name, friends,favorite_topics }; //оцінює повідомлення

    name = "Vanya";
    friends.clear();
    friends.push_back(u1);
    friends.push_back(u2);
    favorite_topics.clear();
    favorite_topics.push_back("topic "+QString::number(rand() % 50));
    favorite_topics.push_back("topic "+QString::number(rand() % 50));
    favorite_topics.push_back("topic "+QString::number(rand() % 50));
    favorite_topics.push_back("topic "+QString::number(rand() % 50));
    favorite_topics.push_back("topic "+QString::number(rand() % 50));
    User u3{ name, friends, favorite_topics }; //оцінює і пересилає повідомлення

    name = "John";
    friends.clear();
    friends.push_back(u1);
    friends.push_back(u2);
    friends.push_back(u3);
    favorite_topics.clear();
    favorite_topics.push_back("topic 1");
    User u4{ name, friends, favorite_topics }; //відповідає на повідомлення

    CreateRandomMessage(nullptr, message_vector, u1, u2, u3, u4, 1);
    CHECK(message_vector.size() != 0);
    CHECK(message_vector[0].GetAdvanceNotice() == nullptr);
    CHECK(message_vector[0].GetType() == MESSAGE_TYPES::NEW_MESSAGE);

    int rating = message_vector[0].GetRating();

    CreateRandomMessage(nullptr, message_vector, u1, u2, u3, u4, 2);
    CHECK(message_vector[0].GetAdvanceNotice() == nullptr);
    CHECK((message_vector[0].GetRating() == rating+1 || message_vector[0].GetRating() == rating-1));
    CHECK(message_vector.size() == 1);

    CreateRandomMessage(nullptr, message_vector, u1, u2, u3, u4, 3);
    CHECK(message_vector.size() == 2);
    CHECK(message_vector[1].GetRating() == message_vector[0].GetRating());
    CHECK(message_vector[1].GetAdvanceNotice() == nullptr);
    CHECK(message_vector[1].GetType() == MESSAGE_TYPES::REPOST_MESSAGE);

    CreateRandomMessage(nullptr, message_vector, u1, u2, u3, u4, 4);
    CHECK(message_vector.size() == 3);
    CHECK(message_vector[2].GetRating() == 0);
    CHECK(message_vector[2].GetType() == MESSAGE_TYPES::REPLY_MESSAGE);
}
#endif
