/*
 * Copyright (C) 2024 klogg contributors
 *
 * This file is part of klogg.
 *
 * klogg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * klogg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with klogg.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SEARCHHISTORYCOMBOBOX_H_
#define SEARCHHISTORYCOMBOBOX_H_

#include <QComboBox>

class SearchHistoryComboBox final : public QComboBox {
    Q_OBJECT

  public:
    explicit SearchHistoryComboBox( QWidget* parent = nullptr );

    ~SearchHistoryComboBox() = default;
    SearchHistoryComboBox( const SearchHistoryComboBox& other ) = delete;
    SearchHistoryComboBox( SearchHistoryComboBox&& other ) noexcept = delete;
    SearchHistoryComboBox& operator=( const SearchHistoryComboBox& other ) = delete;
    SearchHistoryComboBox& operator=( SearchHistoryComboBox&& other ) noexcept = delete;

    virtual void showPopup() override;

  private:
    void showPopupOnCorrectScreen();
};

#endif