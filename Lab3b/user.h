#pragma once
#include <string>
#include <list>
#include <QString>

/// <summary>
/// Class that stores information about the user
/// </summary>
class User {
public:
    User(QString name, std::list <User> friends, std::list <QString> favoriteTopics);

    /// <summary>
    /// The method is used to display the username on the screen
    /// </summary>
    /// <returns>
    ///  Returns the username
    /// </returns>
    inline QString GetName() { return m_Name; }

    /// <returns>
    ///  Returns the user's favorite topic
    /// </returns>
    inline std::list <QString> GetFavoriteTopics() { return m_FavoriteTopics; }
//   inline std::list <User> GetFriends() { return m_Friends; }

private:
    QString m_Name;
    std::list <User> m_Friends;
    std::list <QString> m_FavoriteTopics;
};
