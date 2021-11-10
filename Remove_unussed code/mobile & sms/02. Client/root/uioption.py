Search and delete this:

MOBILE = FALSE

if localeInfo.IsYMIR():
	MOBILE = TRUE

Search and delete this:

		global NO_MOBILE

Search this:

			if MOBILE:
				pyScriptLoader.LoadScriptFile(self, "uiscript/optiondialog_formobile.py")
			else:
				pyScriptLoader.LoadScriptFile(self, "uiscript/optiondialog.py")

change to:

			pyScriptLoader.LoadScriptFile(self, "uiscript/optiondialog.py")

Search this and delete:

			if MOBILE:
				self.inputMobileButton = GetObject("input_mobile_button")
				self.deleteMobileButton = GetObject("delete_mobile_button")

Search this and delete:

		if MOBILE:
			self.inputMobileButton.SetEvent(ui.__mem_func__(self.__OnChangeMobilePhoneNumber))
			self.deleteMobileButton.SetEvent(ui.__mem_func__(self.__OnDeleteMobilePhoneNumber))

Search this and delete:

	def __OnChangeMobilePhoneNumber(self):

		import uiCommon
		inputDialog = uiCommon.InputDialog()
		inputDialog.SetTitle(localeInfo.MESSENGER_INPUT_MOBILE_PHONE_NUMBER_TITLE)
		inputDialog.SetMaxLength(13)
		inputDialog.SetAcceptEvent(ui.__mem_func__(self.OnInputMobilePhoneNumber))
		inputDialog.SetCancelEvent(ui.__mem_func__(self.OnCloseInputDialog))
		inputDialog.Open()
		self.inputDialog = inputDialog

	def __OnDeleteMobilePhoneNumber(self):
		import uiCommon
		questionDialog = uiCommon.QuestionDialog()
		questionDialog.SetText(localeInfo.MESSENGER_DO_YOU_DELETE_PHONE_NUMBER)
		questionDialog.SetAcceptEvent(ui.__mem_func__(self.OnDeleteMobile))
		questionDialog.SetCancelEvent(ui.__mem_func__(self.OnCloseQuestionDialog))
		questionDialog.Open()
		self.questionDialog = questionDialog

	def OnInputMobilePhoneNumber(self):
		text = self.inputDialog.GetText()

		if not text:
			return

		text.replace('-', '')
		net.SendChatPacket("/mobile " + text)
		self.OnCloseInputDialog()
		return TRUE

	def OnInputMobileAuthorityCode(self):
		text = self.inputDialog.GetText()
		net.SendChatPacket("/mobile_auth " + text)
		self.OnCloseInputDialog()
		return TRUE

	def OnDeleteMobile(self):
		net.SendChatPacket("/mobile")
		self.OnCloseQuestionDialog()
		return TRUE

Search this and delete:

	def RefreshMobile(self):
		global MOBILE
		if not MOBILE:
			return

		if player.HasMobilePhoneNumber():
			self.inputMobileButton.Hide()
			self.deleteMobileButton.Show()
		else:
			self.inputMobileButton.Show()
			self.deleteMobileButton.Hide()

	def OnMobileAuthority(self):
		import uiCommon
		inputDialog = uiCommon.InputDialogWithDescription()
		inputDialog.SetTitle(localeInfo.MESSENGER_INPUT_MOBILE_AUTHORITY_TITLE)
		inputDialog.SetDescription(localeInfo.MESSENGER_INPUT_MOBILE_AUTHORITY_DESCRIPTION)
		inputDialog.SetAcceptEvent(ui.__mem_func__(self.OnInputMobileAuthorityCode))
		inputDialog.SetCancelEvent(ui.__mem_func__(self.OnCloseInputDialog))
		inputDialog.SetMaxLength(4)
		inputDialog.SetBoardWidth(310)
		inputDialog.Open()
		self.inputDialog = inputDialog

Search this and delete:

		self.RefreshMobile()


