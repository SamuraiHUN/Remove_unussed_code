Search and delete:

	def IsMobile(self):
		return False

Search and delete:

	def OnMobileMessage(self):
		pass

Search and delete:

	STATE_MOBILE = 2

Search and delete:

		"MOBILE" : "d:/ymir work/ui/game/windows/messenger_list_mobile.sub",

Search and delete:

		self.mobileFlag = False

Search and delete:

	def IsMobile(self):
		if self.STATE_MOBILE == self.state:
			return True

		return False

Search and delete:

	def SetMobile(self, flag):
		self.mobileFlag = flag

		if not self.IsOnline():
			self.Offline()

Search and delete:

	def OnMobileMessage(self):
		if not uiGameOption.MOBILE:
			return

		if not self.IsMobile():
			return

		self.getParentEvent().SendMobileMessage(self.GetName())

Search and delete:

		self.hasMobilePhoneNumber = True

Search and delete:

			self.mobileButton = self.GetChild("MobileButton")

Search and delete:

		self.mobileButton.SetEvent(ui.__mem_func__(self.OnPressMobileButton))

Search and delete:

		if not uiGameOption.MOBILE: #constInfo.SEND_MOBILE_PHONE_MESSAGE_ENABLE:
			self.mobileButton.Hide()
			width = self.GetWidth()
			height = self.GetHeight()

!!!!!!!! If u have messenger block

This:

		if not uiGameOption.MOBILE: #constInfo.SEND_MOBILE_PHONE_MESSAGE_ENABLE:
			self.mobileButton.Hide()
			width = self.GetWidth()
			height = self.GetHeight()
			if not app.ENABLE_MESSENGER_BLOCK:
				self.addFriendButton.SetPosition(-60, 30)
				self.whisperButton.SetPosition(-20, 30)
				self.removeButton.SetPosition(20, 30)
				self.guildButton.SetPosition(60, 30)

change to:

		if not app.ENABLE_MESSENGER_BLOCK:
			self.addFriendButton.SetPosition(-60, 30)
			self.whisperButton.SetPosition(-20, 30)
			self.removeButton.SetPosition(20, 30)
			self.guildButton.SetPosition(60, 30)

Search and delete this:

		self.mobileButton.Disable()

Search and delete this:

		self.mobileButton = None

Search and delete this:

	def SendMobileMessage(self, name):
		if not uiGameOption.MOBILE:
			return

		if not self.hasMobilePhoneNumber:
			questionDialog = uiCommon.QuestionDialog2()
			questionDialog.SetText1(localeInfo.MESSENGER_INPUT_MOBILE_PHONE_NUMBER_1)
			questionDialog.SetText2(localeInfo.MESSENGER_INPUT_MOBILE_PHONE_NUMBER_2)
			questionDialog.SetAcceptEvent(ui.__mem_func__(self.OnAcceptInputMobilePhoneNumber))
			questionDialog.SetCancelEvent(ui.__mem_func__(self.OnCancelInputMobilePhoneNumber))
			questionDialog.SetWidth(400)
			questionDialog.Open()
			self.questionDialog = questionDialog
			return

		## Input Sending Mobile Message
		inputDialog = uiCommon.InputDialog()
		inputDialog.SetTitle(localeInfo.MESSENGER_SEND_MOBILE_MESSAGE_TITLE)
		inputDialog.SetMaxLength(50)
		inputDialog.SetAcceptEvent(ui.__mem_func__(self.OnInputMobileMessage))
		inputDialog.SetCancelEvent(ui.__mem_func__(self.OnCloseInputDialog))
		inputDialog.name = name
		inputDialog.Open()
		self.inputDialog = inputDialog

	def OnAcceptInputMobilePhoneNumber(self):
		if not uiGameOption.MOBILE:
			return

		## Input Mobile Phone Number
		inputDialog = uiCommon.InputDialog()
		inputDialog.SetTitle(localeInfo.MESSENGER_INPUT_MOBILE_PHONE_NUMBER_TITLE)
		inputDialog.SetMaxLength(13)
		inputDialog.SetAcceptEvent(ui.__mem_func__(self.OnInputMobilePhoneNumber))
		inputDialog.SetCancelEvent(ui.__mem_func__(self.OnCloseInputDialog))
		inputDialog.Open()
		self.inputDialog = inputDialog
		self.OnCancelInputMobilePhoneNumber()

	def OnCancelInputMobilePhoneNumber(self):
		if not uiGameOption.MOBILE:
			return
		self.questionDialog.Close()
		self.questionDialog = None
		return True

	def OnInputMobilePhoneNumber(self):
		if not uiGameOption.MOBILE:
			return

		text = self.inputDialog.GetText()

		if not text:
			return

		text.replace('-', '')
		net.SendChatPacket("/mobile " + text)
		self.OnCloseInputDialog()
		return True

	def OnInputMobileMessage(self):
		if not uiGameOption.MOBILE:
			return

		text = self.inputDialog.GetText()

		if not text:
			return

		net.SendMobileMessagePacket(self.inputDialog.name, text)
		self.OnCloseInputDialog()
		return True

Search and delete this:

	def OnPressMobileButton(self):
		if self.selectedItem:
			self.selectedItem.OnMobileMessage()

Search and delete this:

			if self.selectedItem.IsMobile():
				self.mobileButton.Enable()
			else:
				self.mobileButton.Disable()

Search and delete this:

		elif self.selectedItem.IsMobile():
			self.OnPressMobileButton()

Search and delete this:

	def OnMobile(self, groupIndex, key, mobileFlag):
		group = self.groupList[groupIndex]
		member = group.FindMember(key)
		if not member:
			return
		member.SetMobile(mobileFlag)
		self.OnRefreshList()

Search:

	def Offline(self):
		if self.mobileFlag:
			self.image.LoadImage(self.IMAGE_FILE_NAME["MOBILE"])
			self.state = self.STATE_MOBILE

		else:
			self.image.LoadImage(self.IMAGE_FILE_NAME["OFFLINE"])
			self.state = self.STATE_OFFLINE

change to:

	def Offline(self):
		self.image.LoadImage(self.IMAGE_FILE_NAME["OFFLINE"])
		self.state = self.STATE_OFFLINE
