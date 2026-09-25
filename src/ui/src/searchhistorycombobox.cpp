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

#include "searchhistorycombobox.h"

#include <QGuiApplication>
#include <QScreen>
#include <qabstractitemview.h>

SearchHistoryComboBox::SearchHistoryComboBox( QWidget* parent )
    : QComboBox( parent )
{
    setEditable( true );
    setSizeAdjustPolicy( QComboBox::AdjustToMinimumContentsLengthWithIcon );
}

void SearchHistoryComboBox::showPopup()
{
    showPopupOnCorrectScreen();
}

void SearchHistoryComboBox::showPopupOnCorrectScreen()
{
    // Get the global position of the combo box (bottom-left corner)
    QPoint globalPos = mapToGlobal( QPoint( 0, height() ) );

    // Find the screen where the combo box is located
    QScreen* targetScreen = QGuiApplication::screenAt( globalPos );
    if ( !targetScreen ) {
        // Fallback to primary screen if screenAt returns nullptr
        targetScreen = QGuiApplication::primaryScreen();
    }

    // Show the popup first (this creates the view)
    QComboBox::showPopup();

    // Get the popup view
    QAbstractItemView* popupView = view();
    if ( !popupView ) {
        return;
    }

    // Get the screen geometry
    QRect screenGeometry = targetScreen->availableGeometry();

    // Get the popup size
    QSize popupSize = popupView->sizeHint();

    // Calculate the desired position (bottom-left of combo box)
    int x = globalPos.x();
    int y = globalPos.y();

    // Ensure the popup stays within the screen horizontally
    if ( x + popupSize.width() > screenGeometry.right() ) {
        x = screenGeometry.right() - popupSize.width();
    }
    if ( x < screenGeometry.left() ) {
        x = screenGeometry.left();
    }

    // Ensure the popup stays within the screen vertically
    // Try to show below the combo box first
    if ( y + popupSize.height() > screenGeometry.bottom() ) {
        // If it doesn't fit below, show above the combo box
        y = mapToGlobal( QPoint( 0, 0 ) ).y() - popupSize.height();
        if ( y < screenGeometry.top() ) {
            y = screenGeometry.top();
        }
    }
    if ( y < screenGeometry.top() ) {
        y = screenGeometry.top();
    }

    // Move the popup to the correct position
    popupView->move( x, y );
}