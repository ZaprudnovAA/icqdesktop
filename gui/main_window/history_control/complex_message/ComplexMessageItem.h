#pragma once

#include "../../../namespaces.h"
#include "../../../types/message.h"

#include "../MessageItemBase.h"

UI_NS_BEGIN

class ActionButtonWidget;
class ContextMenu;
class HistoryControlPage;
class MessageStatusWidget;
class TextEmojiWidget;

UI_NS_END

UI_THEMES_NS_BEGIN

class theme;

UI_THEMES_NS_END

UI_COMPLEX_MESSAGE_NS_BEGIN

enum class BlockSelectionType;
class ComplexMessageItemLayout;
class IItemBlock;

typedef std::shared_ptr<const QPixmap> QPixmapSCptr;

typedef std::vector<IItemBlock*> IItemBlocksVec;

class ComplexMessageItem final : public MessageItemBase
{
    friend class ComplexMessageItemLayout;

    enum class MenuItemType
    {
        Copy,
        Quote,
        Forward,
    };

    Q_OBJECT

Q_SIGNALS:
    void copy(QString text);

    void quote(QList<Data::Quote>);

    void forward(QList<Data::Quote>);

    void adminMenuRequest(QString);

public:
    ComplexMessageItem(
        QWidget *parent,
        const int64_t id,
        const QDate date,
        const QString &chatAimid,
        const QString &senderAimid,
        const QString &senderFriendly,
        const QString &sourceText,
        const bool isOutgoing);

    virtual void clearSelection() override;

    virtual QString formatRecentsText() const override;

    qint64 getId() const override;

    QString getQuoteHeader() const;

    QString getSelectedText(const bool isQuote) const;

    const QString& getChatAimid() const;

    QDate getDate() const;

    const QString& getSenderAimid() const;

    QString getSenderFriendly() const;

    std::shared_ptr<const themes::theme> getTheme() const;

    virtual bool isOutgoing() const override;

    bool isSimple() const;

    bool isUpdateable() const;

    void onBlockSizeChanged();

    void onHoveredBlockChanged(IItemBlock *newHoveredBlock);

    void onStyleChanged();

    virtual void onActivityChanged(const bool isActive) override;

    virtual void onVisibilityChanged(const bool isVisible) override;

    void replaceBlockWithSourceText(IItemBlock *block);

    void selectByPos(const QPoint& from, const QPoint& to);

    void setChatAdminFlag(const bool isChatAdmin);

    virtual void setHasAvatar(const bool value) override;

    void setItems(IItemBlocksVec blocks);

    void setMchatSender(const QString& sender);

    virtual bool setLastRead(const bool isLastRead) final override;

    void setTime(const int32_t time);

    int32_t getTime() const;

    virtual QSize sizeHint() const override;

    void updateWith(ComplexMessageItem &update);

    bool isSelected() const override;

    QList<Data::Quote> getQuotes(bool force = false) const;

    void setSourceText(const QString& text);

protected:
    bool isChatAdmin() const;

    virtual void leaveEvent(QEvent *event) override;

    virtual void mouseMoveEvent(QMouseEvent *event) override;

    virtual void mousePressEvent(QMouseEvent *event) override;

    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    virtual void paintEvent(QPaintEvent *event) override;

private Q_SLOTS:
    void onAvatarChanged(QString aimId);

    void onMenuItemTriggered(QAction *action);

private:
    void addBlockMenuItems(const QPoint &pos);

    void cleanupMenu();

    void createSenderControl();

    void connectSignals();

    bool containsShareableBlocks() const;

    void drawAvatar(QPainter &p);

    void drawBlocksSeparators(QPainter &p);

    void drawBubble(QPainter &p);

    QString getBlocksText(const IItemBlocksVec &items, const bool isSelected, const bool isQuote) const;

    void drawGrid(QPainter &p);

    void drawLastRead(QPainter &p);

    IItemBlock* findBlockUnder(const QPoint &pos) const;

    bool hasSeparator(const IItemBlock *block) const;

    void initialize();

    void initializeShareButton();

    bool isBubbleRequired() const;

    bool isOverAvatar(const QPoint &pos) const;

    bool isSenderVisible() const;

    void loadAvatar();

    void onCopyMenuItem(MenuItemType type);

    bool onDeveloperMenuItemTriggered(const QString &cmd);

    void onShareButtonClicked();

    void trackMenu(const QPoint &globalPos);

    void updateSenderControlColor();

    void updateShareButtonGeometry();

    QPixmapSCptr Avatar_;

    IItemBlocksVec Blocks_;

    QPainterPath Bubble_;

    QRect BubbleGeometry_;

    QString ChatAimid_;

    QDate Date_;

    BlockSelectionType FullSelectionType_;

    IItemBlock *HoveredBlock_;

    int64_t Id_;

    bool Initialized_;

    bool IsChatAdmin_;

    bool IsLastRead_;

    bool IsOutgoing_;

    ComplexMessageItemLayout *Layout_;

    ContextMenu *Menu_;

    IItemBlock *MenuBlock_;

    bool MouseLeftPressedOverAvatar_;

    bool MouseRightPressedOverItem_;

    TextEmojiWidget *Sender_;

    QString SenderAimid_;

    QString SenderFriendly_;

    ActionButtonWidget *ShareButton_;

    QString SourceText_;

    MessageStatusWidget *Status_;

    int32_t Time_;

};

UI_COMPLEX_MESSAGE_NS_END