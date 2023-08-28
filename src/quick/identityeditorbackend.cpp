// SPDX-FileCopyrightText: 2023 Claudio Cambra <claudio.cambra@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include "identityeditorbackend.h"

#include <memory>

namespace KIdentityManagement
{
namespace Quick
{

IdentityEditorBackend::Mode IdentityEditorBackend::mode() const
{
    return m_mode;
}

void IdentityEditorBackend::setMode(Mode mode)
{
    if (m_mode == mode) {
        return;
    }

    m_mode = mode;
    Q_EMIT modeChanged();
}

Identity IdentityEditorBackend::identity() const
{
    return m_identity;
}

void IdentityEditorBackend::setIdentity(const Identity &identity)
{
    if (m_identity == identity) {
        return;
    }

    m_identity = identity;
    Q_EMIT identityChanged();
}

uint IdentityEditorBackend::identityUoid() const
{
    return m_identity.uoid();
}

void IdentityEditorBackend::setIdentityUoid(uint identityUoid)
{
    if (m_identity.uoid() == identityUoid) {
        return;
    }

    const auto &identity = m_identityManager->modifyIdentityForUoid(identityUoid);
    setIdentity(identity);
}

void IdentityEditorBackend::saveIdentity(const Identity &modifiedIdentity)
{
    m_identityManager->saveIdentity(modifiedIdentity);
}

void IdentityEditorBackend::addEmailAlias(const QString &alias)
{
    auto aliases = m_identity.emailAliases();
    aliases.append(alias);
    m_identity.setEmailAliases(aliases);
}

void IdentityEditorBackend::modifyEmailAlias(const QString &originalAlias, const QString &modifiedAlias)
{
    auto aliases = m_identity.emailAliases();
    std::replace(aliases.begin(), aliases.end(), originalAlias, modifiedAlias);
    m_identity.setEmailAliases(aliases);
}

void IdentityEditorBackend::removeEmailAlias(const QString &alias)
{
    auto aliases = m_identity.emailAliases();
    aliases.removeAll(alias);
    m_identity.setEmailAliases(aliases);
}
}
}
