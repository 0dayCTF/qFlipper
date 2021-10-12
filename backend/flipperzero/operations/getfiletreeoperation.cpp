#include "getfiletreeoperation.h"

#include <QTimer>

#include "flipperzero/flipperzero.h"
#include "flipperzero/storagecontroller.h"
#include "flipperzero/storage/listoperation.h"

#include "macros.h"

using namespace Flipper;
using namespace Zero;

GetFileTreeOperation::GetFileTreeOperation(FlipperZero *device, const QByteArray &rootPath, QObject *parent):
    Operation(device, parent),
    m_rootPath(rootPath),
    m_pendingCount(0)
{}

const QString GetFileTreeOperation::description() const
{
    return QStringLiteral("Get File Tree @%1").arg(QString(m_rootPath));
}

const FileInfoList &GetFileTreeOperation::result() const
{
    return m_result;
}

void GetFileTreeOperation::transitionToNextState()
{
    if(state() == BasicState::Ready) {
        setState(State::Running);
        listDirectory(m_rootPath);

    } else if(state() == State::Running) {
        --m_pendingCount;
        auto *op = qobject_cast<ListOperation*>(sender());

        if(op->isError()) {
            finishWithError(op->errorString());
            return;
        }

        for(const auto &fileInfo : qAsConst(op->result())) {
            if(fileInfo.type == FileType::Directory) {
                listDirectory(fileInfo.absolutePath);
            }

            m_result.push_back(fileInfo);
        }

        op->deleteLater();

        if(!m_pendingCount) {
            finish();
        }
    }
}

void GetFileTreeOperation::listDirectory(const QByteArray &path)
{
    ++m_pendingCount;
    auto *op = device()->storage()->list(path);
    connect(op, &AbstractOperation::finished, this, &GetFileTreeOperation::transitionToNextState);
}