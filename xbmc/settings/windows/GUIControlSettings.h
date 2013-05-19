#pragma once
/*
 *      Copyright (C) 2005-2012 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "utils/StdString.h"

class CGUIControl;
class CGUIImage;
class CGUISpinControlEx;
class CGUIEditControl;
class CGUIButtonControl;
class CGUIRadioButtonControl;

class CSetting;
class CSettingPath;

class CGUIControlBaseSetting
{
public:
  CGUIControlBaseSetting(int id, CSetting *pSetting);
  virtual ~CGUIControlBaseSetting() {}
  
  int GetID() { return m_id; }
  CSetting* GetSetting() { return m_pSetting; }

  /*!
   \brief Specifies that this setting should update after a delay
   Useful for settings that have options to navigate through
   and may take a while, or require additional input to update
   once the final setting is chosen.  Settings default to updating
   instantly.
   \sa IsDelayed()
   */
  void SetDelayed() { m_delayed = true; }

  /*!
   \brief Returns whether this setting should have delayed update
   \return true if the setting's update should be delayed
   \sa SetDelayed()
   */
  bool IsDelayed() const { return m_delayed; }

  /*!
   \brief Specifies that this setting is enabled or disabled
   This is used for settings which are enabled/disabled based
   on conditions involving other settings and their values.
   It must not be confused with a setting spin control being
   disabled because it contains less than two items.
   \param enabled Whether the setting is enabled or disabled
   \sa IsEnabled()
   */
  void SetEnabled(bool enabled) { m_enabled = enabled; }

  /*!
   \brief Returns whether this setting is enabled or disabled
   This state is independent of the real enabled state of a
   setting control but represents the enabled state of the
   setting itself based on specific conditions.
   \return true if the setting is enabled otherwise false
   \sa SetEnabled()
   */
  bool IsEnabled() const { return m_enabled; }

  virtual CGUIControl* GetControl() { return NULL; }
  virtual bool OnClick() { return false; }
  virtual void Update();
  virtual void Clear() = 0;  ///< Clears the attached control
protected:
  int m_id;
  CSetting* m_pSetting;
  bool m_delayed;
  bool m_enabled;
};

class CGUIControlRadioButtonSetting : public CGUIControlBaseSetting
{
public:
  CGUIControlRadioButtonSetting(CGUIRadioButtonControl* pRadioButton, int id, CSetting *pSetting);
  virtual ~CGUIControlRadioButtonSetting();

  void Select(bool bSelect);

  virtual CGUIControl* GetControl() { return (CGUIControl*)m_pRadioButton; }
  virtual bool OnClick();
  virtual void Update();
  virtual void Clear() { m_pRadioButton = NULL; }
private:
  CGUIRadioButtonControl *m_pRadioButton;
};

class CGUIControlSpinExSetting : public CGUIControlBaseSetting
{
public:
  CGUIControlSpinExSetting(CGUISpinControlEx* pSpin, int id, CSetting *pSetting);
  virtual ~CGUIControlSpinExSetting();

  virtual CGUIControl* GetControl() { return (CGUIControl*)m_pSpin; }
  virtual bool OnClick();
  virtual void Update();
  virtual void Clear() { m_pSpin = NULL; }
private:
  CGUISpinControlEx *m_pSpin;
};

class CGUIControlButtonSetting : public CGUIControlBaseSetting
{
public:
  CGUIControlButtonSetting(CGUIButtonControl* pButton, int id, CSetting *pSetting);
  virtual ~CGUIControlButtonSetting();

  virtual CGUIControl* GetControl() { return (CGUIControl*)m_pButton; }
  virtual bool OnClick();
  virtual void Update();
  virtual void Clear() { m_pButton = NULL; }

  static bool GetPath(CSettingPath *pathSetting);
private:
  CGUIButtonControl *m_pButton;
};

class CGUIControlEditSetting : public CGUIControlBaseSetting
{
public:
  CGUIControlEditSetting(CGUIEditControl* pButton, int id, CSetting *pSetting);
  virtual ~CGUIControlEditSetting();

  virtual CGUIControl* GetControl() { return (CGUIControl*)m_pEdit; }
  virtual bool OnClick();
  virtual void Update();
  virtual void Clear() { m_pEdit = NULL; }
private:
  CGUIEditControl *m_pEdit;
};

class CGUIControlSeparatorSetting : public CGUIControlBaseSetting
{
public:
  CGUIControlSeparatorSetting(CGUIImage* pImage, int id);
  virtual ~CGUIControlSeparatorSetting();

  virtual CGUIControl* GetControl() { return (CGUIControl*)m_pImage; }
  virtual bool OnClick() { return false; }
  virtual void Update() {}
  virtual void Clear() { m_pImage = NULL; }
private:
  CGUIImage *m_pImage;
};
