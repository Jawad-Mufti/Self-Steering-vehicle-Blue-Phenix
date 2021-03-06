/*
 * Copyright (C) 2017-2018  Christian Berger
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CLUON_FROMMSGPACKVISITOR_HPP
#define CLUON_FROMMSGPACKVISITOR_HPP

#include "cluon/MsgPackConstants.hpp"
#include "cluon/any/any.hpp"
#include "cluon/cluon.hpp"

#include <cstdint>
#include <istream>
#include <map>
#include <string>

namespace cluon {
/**
This class decodes a given message from MsgPack format.
*/
class LIBCLUON_API FromMsgPackVisitor {
    /**
     * This class represents a key/value in a MsgPack payload stream of key/values.
     */
    class MsgPackKeyValue {
       private:
        MsgPackKeyValue &operator=(MsgPackKeyValue &&) = delete;

       public:
        MsgPackKeyValue()                        = default;
        MsgPackKeyValue(const MsgPackKeyValue &) = default;
        MsgPackKeyValue(MsgPackKeyValue &&)      = default;
        MsgPackKeyValue &operator=(const MsgPackKeyValue &) = default;
        ~MsgPackKeyValue()                                  = default;

       public:
        std::string m_key{""};
        MsgPackConstants m_formatFamily{MsgPackConstants::BOOL_FORMAT};
        linb::any m_value;
    };

   private:
    FromMsgPackVisitor(const FromMsgPackVisitor &) = delete;
    FromMsgPackVisitor(FromMsgPackVisitor &&)      = delete;
    FromMsgPackVisitor &operator=(FromMsgPackVisitor &&) = delete;
    FromMsgPackVisitor &operator=(const FromMsgPackVisitor &other) = delete;

    /**
     * Internal constructor to pass reference to preset key/values.
     *
     * @param preset Pre-filled key/value map to handle nested fields.
     */
    FromMsgPackVisitor(std::map<std::string, FromMsgPackVisitor::MsgPackKeyValue> &preset) noexcept;

   public:
    FromMsgPackVisitor() noexcept;
    ~FromMsgPackVisitor() = default;

   public:
    /**
     * This method decodes a given istream into an internal key/value representation.
     *
     * @param in istream to decode.
     */
    void decodeFrom(std::istream &in) noexcept;

   public:
    // The following methods are provided to allow an instance of this class to
    // be used as visitor for an instance with the method signature void accept<T>(T&);

    void preVisit(int32_t id, const std::string &shortName, const std::string &longName) noexcept;
    void postVisit() noexcept;

    void visit(uint32_t id, std::string &&typeName, std::string &&name, bool &v) noexcept;
    void visit(uint32_t id, std::string &&typeName, std::string &&name, char &v) noexcept;
    void visit(uint32_t id, std::string &&typeName, std::string &&name, int8_t &v) noexcept;
    void visit(uint32_t id, std::string &&typeName, std::string &&name, uint8_t &v) noexcept;
    void visit(uint32_t id, std::string &&typeName, std::string &&name, int16_t &v) noexcept;
    void visit(uint32_t id, std::string &&typeName, std::string &&name, uint16_t &v) noexcept;
    void visit(uint32_t id, std::string &&typeName, std::string &&name, int32_t &v) noexcept;
    void visit(uint32_t id, std::string &&typeName, std::string &&name, uint32_t &v) noexcept;
    void visit(uint32_t id, std::string &&typeName, std::string &&name, int64_t &v) noexcept;
    void visit(uint32_t id, std::string &&typeName, std::string &&name, uint64_t &v) noexcept;
    void visit(uint32_t id, std::string &&typeName, std::string &&name, float &v) noexcept;
    void visit(uint32_t id, std::string &&typeName, std::string &&name, double &v) noexcept;
    void visit(uint32_t id, std::string &&typeName, std::string &&name, std::string &v) noexcept;

    template <typename T>
    void visit(uint32_t &id, std::string &&typeName, std::string &&name, T &value) noexcept {
        (void)id;
        (void)typeName;

        if (0 < m_keyValues.count(name)) {
            try {
                std::map<std::string, FromMsgPackVisitor::MsgPackKeyValue> v
                    = linb::any_cast<std::map<std::string, FromMsgPackVisitor::MsgPackKeyValue>>(m_keyValues[name].m_value);
                cluon::FromMsgPackVisitor nestedMsgPackDecoder(v);
                value.accept(nestedMsgPackDecoder);
            } catch (const linb::bad_any_cast &) { // LCOV_EXCL_LINE
            }
        }
    }

   private:
    MsgPackConstants getFormatFamily(uint8_t T) noexcept;
    std::map<std::string, FromMsgPackVisitor::MsgPackKeyValue> readKeyValues(std::istream &in) noexcept;
    uint64_t readUint(std::istream &in) noexcept;
    int64_t readInt(std::istream &in) noexcept;
    std::string readString(std::istream &in) noexcept;

   private:
    std::map<std::string, FromMsgPackVisitor::MsgPackKeyValue> m_data{};
    std::map<std::string, FromMsgPackVisitor::MsgPackKeyValue> &m_keyValues;
};
} // namespace cluon

#endif
