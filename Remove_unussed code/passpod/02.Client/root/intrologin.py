delete this:

NEWCIBN_PASSPOD_AUTH = False

and this:

PASSPOD_MSG_DICT = {}

and this:

	NEWCIBN_PASSPOD_AUTH = True
	PASSPOD_MSG_DICT = {
		"PASERR1" : localeInfo.LOGIN_FAILURE_PASERR1,
		"PASERR2" : localeInfo.LOGIN_FAILURE_PASERR2,
		"PASERR3" : localeInfo.LOGIN_FAILURE_PASERR3,
		"PASERR4" : localeInfo.LOGIN_FAILURE_PASERR4,
		"PASERR5" : localeInfo.LOGIN_FAILURE_PASERR5,
	}
	
and this:

	PASSPOD_MSG_DICT = {
		"NOTELE" : localeInfo.LOGIN_FAILURE_NOTELEBLOCK,
	}

and this:

def IsNEWCIBNPassPodAuth():
	global NEWCIBN_PASSPOD_AUTH
	return NEWCIBN_PASSPOD_AUTH

and this:

		# NEWCIBN_PASSPOD_AUTH
		self.passpodBoard = None
		self.passpodAnswerInput = None
		self.passpodAnswerOK = None
		self.passpodAnswerCancel = None
		# NEWCIBN_PASSPOD_AUTH_END

and this:

		try:
			loginFailureMsg = self.loginFailureMsgDict[error]
		except KeyError:
			if PASSPOD_MSG_DICT:
				try:
					loginFailureMsg = PASSPOD_MSG_DICT[error]
				except KeyError:
					loginFailureMsg = localeInfo.LOGIN_FAILURE_UNKNOWN + error
			else:
				loginFailureMsg = localeInfo.LOGIN_FAILURE_UNKNOWN + error

change to:

		try:
			loginFailureMsg = self.loginFailureMsgDict[error]
		except KeyError:
			loginFailureMsg = localeInfo.LOGIN_FAILURE_UNKNOWN + error
			

and search this and delete:

			# NEWCIBN_PASSPOD_AUTH
			if IsNEWCIBNPassPodAuth():
				self.passpodBoard = GetObject("NEWCIBN_PASSPOD_BOARD")
				self.passpodAnswerInput = GetObject("NEWCIBN_PASSPOD_INPUT")
				self.passpodAnswerOK = GetObject("NEWCIBN_PASSPOD_OK")
				self.passpodAnswerCancel = GetObject("NEWCIBN_PASSPOD_CANCEL")
			# NEWCIBN_PASSPOD_AUTH_END

and this:

		# NEWCIBN_PASSPOD_AUTH
		if IsNEWCIBNPassPodAuth():
			self.passpodAnswerOK.SAFE_SetEvent(self.__OnClickNEWCIBNPasspodAnswerOK)
			self.passpodAnswerCancel.SAFE_SetEvent(self.__OnClickNEWCIBNPasspodAnswerCancel)
			self.passpodAnswerInput.SAFE_SetReturnEvent(self.__OnClickNEWCIBNPasspodAnswerOK)

		# NEWCIBN_PASSPOD_AUTH_END

and this:

	# NEWCIBN_PASSPOD_AUTH
	def BINARY_OnNEWCIBNPasspodRequest(self):
		if not IsNEWCIBNPassPodAuth():
			return

		if self.connectingDialog:
			self.connectingDialog.Close()
		self.connectingDialog = None

		self.stream.popupWindow.Close()
		self.serverBoard.Hide()
		self.connectBoard.Hide()
		self.loginBoard.Hide()
		self.passpodBoard.Show()
		self.passpodAnswerInput.SetFocus()

	def BINARY_OnNEWCIBNPasspodFailure(self):
		if not IsNEWCIBNPassPodAuth():
			return

	def __OnClickNEWCIBNPasspodAnswerOK(self):
		answer = self.passpodAnswerInput.GetText()

		print "passpod.ok"
		net.SendNEWCIBNPasspodAnswerPacket(answer)
		self.passpodAnswerInput.SetText("")
		self.passpodBoard.Hide()

		self.stream.popupWindow.Close()
		self.stream.popupWindow.Open(localeInfo.WAIT_FOR_PASSPOD, 
			self.__OnClickNEWCIBNPasspodAnswerCancel, 
			localeInfo.UI_CANCEL)

	def __OnClickNEWCIBNPasspodAnswerCancel(self):
		print "passpod.cancel"

		if self.passpodBoard:
			self.passpodBoard.Hide()

		if self.connectBoard:
			self.connectBoard.Show()

		if self.loginBoard:
			self.loginBoard.Show()

	# NEWCIBN_PASSPOD_AUTH_END

and this:

		# NEWCIBN_PASSPOD_AUTH
		if IsNEWCIBNPassPodAuth():
			self.passpodBoard.Hide()
		# NEWCIBN_PASSPOD_AUTH_END

and  this:

		# NEWCIBN_PASSPOD_AUTH
		if IsNEWCIBNPassPodAuth():
			self.passpodBoard.Hide()
		# NEWCIBN_PASSPOD_AUTH_END

