#ifndef TRACKNUMBERS_H
#define TRACKNUMBERS_H

#include <QString>
#include <QMetaType>


// DTO for storing the current and total number of tracks for an album.
// Both numbers are 1-based and 0 indicates an undefined value.
class TrackNumbers final {
public:
    // TODO(uklotzde): Replace 'const' with 'constexpr'
    static const int kValueUndefined = 0;
    static const int kValueMin = 1; // lower bound (inclusive)

    // Separates the total number of tracks from the current
    // track number in the textual format.
    static const QString kSeparator;

    static bool isUndefinedValue(int value) {
        return kValueUndefined == value;
    }

    static bool isValidValue(int value) {
        return isUndefinedValue(value) || (kValueMin <= value);
    }

    explicit TrackNumbers(int current = kValueUndefined, int total = kValueUndefined)
        : m_current(current),
          m_total(total) {
    }

    bool hasCurrent() const {
        return !isUndefinedValue(m_current);
    }
    bool isCurrentValid() const {
        return isValidValue(m_current);
    }
    int getCurrent() const {
        return m_current;
    }
    void setCurrent(int current) {
        m_current = current;
    }

    bool hasTotal() const {
        return !isUndefinedValue(m_total);
    }
    bool isTotalValid() const {
        return isValidValue(m_total);
    }
    int getTotal() const {
        return m_total;
    }
    void setTotal(int total) {
        m_total = total;
    }

    bool isValid() const {
        return isCurrentValid() && isTotalValid();
    }

    enum class ParseResult {
        EMPTY,
        VALID,
        INVALID
    };

    static ParseResult parseFromStrings(
            const QString& currentText,
            const QString& totalText,
            TrackNumbers* pParsed);
    static ParseResult parseFromString(
            const QString& str,
            TrackNumbers* pParsed);

    void toStrings(
            QString* pCurrentText,
            QString* pTotalText) const;
    QString toString() const;

    // Splits a string into current and total part
    static void splitString(
            const QString& str,
            QString* pCurrentText,
            QString* pTotalText);
    // Joins the current and total strings
    static QString joinStrings(
            const QString& currentText,
            const QString& totalText);

private:
    int m_current;
    int m_total;
};

inline
bool operator==(const TrackNumbers& lhs, const TrackNumbers& rhs) {
    return (lhs.getCurrent() == rhs.getCurrent()) &&
            (lhs.getTotal() == rhs.getTotal());
}

inline
bool operator!=(const TrackNumbers& lhs, const TrackNumbers& rhs) {
    return !(lhs == rhs);
}

Q_DECLARE_METATYPE(TrackNumbers)

#endif // TRACKNUMBERS_H
