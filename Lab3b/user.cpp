#include "user.h"
#include "QString"

User::User(QString name, std::list <User> friends, std::list <QString> favoriteTopics)
        : m_Name(name),
          m_Friends(friends),
          m_FavoriteTopics(favoriteTopics){ }
