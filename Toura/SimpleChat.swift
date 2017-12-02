//
//  SimpleChat.swift
//  Toura
//
//  Created by Carpenter, Deepak (US - Bengaluru) on 02/12/17.
//  Copyright © 2017 TechMusketeers. All rights reserved.
//

import Foundation
import UIKit
class ChatMessage : NSObject {
    
    enum SentBy : String {
        case User = "ChatMessageSentByUser"
        case Opponent = "ChatMessageSentByOpponent"
    }
    
    // MARK: ObjC Compatibility
    
    /*
     ObjC can't interact w/ enums properly, so this is used for converting compatible values.
     */
    
    var color : UIColor? = nil
    
    class func SentByUserString() -> String {
        return ChatMessage.SentBy.User.rawValue
    }
    
    class func SentByOpponentString() -> String {
        return ChatMessage.SentBy.Opponent.rawValue
    }
    
    var sentByString: String {
        get {
            return sentBy.rawValue
        }
        set {
            if let sentBy = SentBy(rawValue: newValue) {
                self.sentBy = sentBy
            } else {
                print("ChatMessage.Error : Property Set : Incompatible string set to SentByString!")
            }
        }
    }
    
    // MARK: Public Properties
    
    var sentBy: SentBy
    var content: String
    var timeStamp: TimeInterval?
    var image : UIImage?
    
    required init (content: String, sentBy: SentBy, timeStamp: TimeInterval? = nil, image: UIImage? = UIImage()){
        self.sentBy = sentBy
        self.timeStamp = timeStamp
        self.content = content
    }
    
    
    // MARK: ObjC Compatibility
    
    convenience init (content: String, sentByString: String) {
        if let sentBy = SentBy(rawValue: sentByString) {
            self.init(content: content, sentBy: sentBy, timeStamp: nil)
        } else {
            fatalError("ChatMessage.FatalError : Initialization : Incompatible string set to SentByString!")
        }
    }
    
    convenience init (content: String, sentByString: String, timeStamp: TimeInterval) {
        if let sentBy = SentBy(rawValue: sentByString) {
            self.init(content: content, sentBy: sentBy, timeStamp: timeStamp)
        } else {
            fatalError("ChatMessage.FatalError : Initialization : Incompatible string set to SentByString!")
        }
    }
    
    convenience init (content: String, sentByString: String, image: UIImage) {
        if let sentBy = SentBy(rawValue: sentByString) {
            self.init(content: content, sentBy: sentBy, image: image)
        } else {
            fatalError("ChatMessage.FatalError : Initialization : Incompatible string set to SentByString!")
        }
    }
}

// MARK: Message Cell

class ChatMessageCell : UITableViewCell {
    
    // MARK: Global MessageCell Appearance Modifier
    
    struct Appearance {
        static var opponentColor = UIColor.fromHex("579FF3")//(red: 0.142954, green: 0.60323, blue: 0.862548, alpha: 0.88)
        static var userColor = UIColor.fromHex("FFFFFF")//(red: 0.14726, green: 0.838161, blue: 0.533935, alpha: 1)
        static var font: UIFont = UIFont.systemFont(ofSize: 15.0)
    }
    
    /*
     These methods are included for ObjC compatibility.  If using Swift, you can set the Appearance variables directly.
     */
    
    class func setAppearanceOpponentColor(_ opponentColor: UIColor) {
        Appearance.opponentColor = opponentColor
    }
    
    class func setAppearanceUserColor(_ userColor: UIColor) {
        Appearance.userColor = userColor
    }
    
    class  func setAppearanceFont(_ font: UIFont) {
        Appearance.font = font
    }
    
    // MARK: Message Bubble TextView
    
    fileprivate lazy var textView: MessageBubbleTextView = {
        let textView = MessageBubbleTextView(frame: CGRect.zero, textContainer: nil)
        self.contentView.addSubview(textView)
        return textView
    }()
    
    fileprivate class MessageBubbleTextView : UITextView {
        
        override init(frame: CGRect = CGRect.zero, textContainer: NSTextContainer? = nil) {
            super.init(frame: frame, textContainer: textContainer)
            self.font = Appearance.font
            self.isScrollEnabled = false
            self.isEditable = false
            self.textContainerInset = UIEdgeInsets(top: 7, left: 7, bottom: 7, right: 7)
            self.layer.cornerRadius = 15
            self.layer.borderWidth = 2.0
        }
        
        required init(coder aDecoder: NSCoder) {
            fatalError("init(coder:) has not been implemented")
        }
    }
    
    // MARK: ImageView
    
    fileprivate lazy var userImageView: UIImageView = {
        let userImageView = UIImageView()
        userImageView.isHidden = true
        userImageView.bounds.size = CGSize(width: self.minimumHeight, height: self.minimumHeight)
        let halfWidth = userImageView.bounds.width / 2.0
        let halfHeight = userImageView.bounds.height / 2.0
        
        // Center the imageview vertically to the textView when it is singleLine
        let textViewSingleLineCenter = self.textView.textContainerInset.top + (Appearance.font.lineHeight / 2.0)
        userImageView.center = CGPoint(x: self.padding + halfWidth, y: textViewSingleLineCenter)
        userImageView.backgroundColor = UIColor.lightText
        userImageView.layer.rasterizationScale = UIScreen.main.scale
        userImageView.layer.shouldRasterize = true
        userImageView.layer.cornerRadius = halfHeight
        userImageView.layer.masksToBounds = true
        self.contentView.addSubview(userImageView)
        return userImageView
    }()
    
    fileprivate lazy var opponentImageView: UIImageView = {
        let opponentImageView = UIImageView()
        opponentImageView.isHidden = true
        opponentImageView.bounds.size = CGSize(width: self.minimumHeight, height: self.minimumHeight)
        let halfWidth = opponentImageView.bounds.width / 2.0
        let halfHeight = opponentImageView.bounds.height / 2.0
        
        // Center the imageview vertically to the textView when it is singleLine
        let textViewSingleLineCenter = self.textView.textContainerInset.top + (Appearance.font.lineHeight / 2.0)
        opponentImageView.center = CGPoint(x: self.padding + halfWidth, y: textViewSingleLineCenter)
        opponentImageView.backgroundColor = UIColor.lightText
        opponentImageView.layer.rasterizationScale = UIScreen.main.scale
        opponentImageView.layer.shouldRasterize = true
        opponentImageView.layer.cornerRadius = halfHeight
        opponentImageView.layer.masksToBounds = true
        self.contentView.addSubview(opponentImageView)
        return opponentImageView
    }()
    
    // MARK: Sizing
    
    fileprivate let padding: CGFloat = 5.0
    
    fileprivate let minimumHeight: CGFloat = 30.0 // arbitrary minimum height
    
    fileprivate var size = CGSize.zero
    
    fileprivate var maxSize: CGSize {
        get {
            let maxWidth = self.bounds.width * 0.75 // Cells can take up to 3/4 of screen
            let maxHeight = CGFloat.greatestFiniteMagnitude
            return CGSize(width: maxWidth, height: maxHeight)
        }
    }
    
    // MARK: Setup Call
    
    /*!
     Use this in cellForRowAtIndexPath to setup the cell.
     */
    func urlDetector(text : String)-> Bool{
        var isURL = false
        let string = text
        let types: NSTextCheckingResult.CheckingType = .link
        let detector = try? NSDataDetector(types: types.rawValue)
        detector?.enumerateMatches(in: string, options: [], range: NSMakeRange(0, (string as NSString).length)) { (result, flags, _) in
            if(result?.url != nil){
                isURL = true
            }
        }
        return isURL
    }
    
    func setupWithMessage(_ message: ChatMessage) -> CGSize {
        textView.text = message.content
        size = textView.sizeThatFits(maxSize)
        if size.height < minimumHeight {
            size.height = minimumHeight
        }
        textView.bounds.size = size
        self.styleTextViewForSentBy(message.sentBy)
        if let color = message.color {
            self.textView.layer.borderColor = color.cgColor
        }
        return size
    }
    
    // MARK: TextBubble Styling
    
    fileprivate func styleTextViewForSentBy(_ sentBy: ChatMessage.SentBy) {
        let halfTextViewWidth = self.textView.bounds.width / 2.0
        let targetX = halfTextViewWidth + padding
        let halfTextViewHeight = self.textView.bounds.height / 2.0
        self.textView.textColor = UIColor.white
        self.backgroundColor = UIColor.clear
        switch sentBy {
        case .Opponent:
            self.textView.center.x = targetX
            self.textView.center.y = halfTextViewHeight
            self.textView.layer.borderColor = Appearance.opponentColor.cgColor
            self.textView.backgroundColor = UIColor.fromHex("579FF3")
            
            if self.opponentImageView.image != nil {
                self.opponentImageView.isHidden = false
                self.textView.center.x += self.opponentImageView.bounds.width + padding
            }
            
        case .User:
            //self.opponentImageView.isHidden = true
            self.textView.center.x = self.bounds.width - targetX
            self.textView.center.y = halfTextViewHeight
            self.textView.layer.borderColor = Appearance.userColor.cgColor
            self.textView.textColor = UIColor.fromHex("4E5974")
            self.textView.backgroundColor = Appearance.userColor
        }
        
    }
}

// MARK: Chat Controller
extension ChatController: ChatControllerDelegate {
    func reloadMeassages(isReload: Bool) {
        tableView.reloadData()
        self.scrollToBottom()
    }
}

@objc protocol ChatControllerDelegate {
    @objc optional func shouldChatController(_ chatController: ChatController, addMessage message: ChatMessage) -> Bool
    @objc optional func chatController(_ chatController: ChatController, didAddNewMessage message: ChatMessage)
    func reloadMeassages(isReload : Bool)
}

class ChatController : UIViewController, UITableViewDelegate, UITableViewDataSource, ChatInputDelegate {
    
    // MARK: Constants
    
    fileprivate struct Constants {
        static let MessagesSection: Int = 0;
        static let MessageCellIdentifier: String = "ChatController.Constants.MessageCellIdentifier"
    }
    
    // MARK: Public Properties
    
    /*!
     Use this to set the messages to be displayed
     */
    var messages: [ChatMessage] = []
    var opponentImage: UIImage?
    var userImage: UIImage?
    
    weak var delegate: ChatControllerDelegate?
    
    // MARK: Private Properties
    
    fileprivate let sizingCell = ChatMessageCell()
    fileprivate let tableView: UITableView = UITableView()
    fileprivate let chatInput = ChatInput(frame: CGRect.zero)
    fileprivate var bottomChatInputConstraint: NSLayoutConstraint!
    
    
    // MARK: Life Cycle
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.setup()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        self.listenForKeyboardChanges()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        self.scrollToBottom()
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        self.unregisterKeyboardObservers()
    }
    
    deinit {
        /*
         Need to remove delegate and datasource or they will try to send scrollView messages.
         */
        self.tableView.delegate = nil
        self.tableView.dataSource = nil
    }
    
    // MARK: Setup
    
    fileprivate func setup() {
        self.setupTableView()
        self.setupChatInput()
        self.setupLayoutConstraints()
    }
    
    fileprivate func setupTableView() {
        tableView.allowsSelection = false
        tableView.separatorStyle = .none
        tableView.frame = self.view.bounds
        tableView.register(ChatMessageCell.classForCoder(), forCellReuseIdentifier: "identifier")
        tableView.delegate = self
        tableView.dataSource = self
        tableView.contentInset = UIEdgeInsets(top: 10, left: 0, bottom: 0, right: 0)
        self.view.backgroundColor = UIColor.fromHex("F0F3F5")
        tableView.backgroundColor = UIColor.clear
        self.view.addSubview(tableView)
    }
    
    fileprivate func setupChatInput() {
        chatInput.delegate = self
        self.view.addSubview(chatInput)
    }
    
    fileprivate func setupLayoutConstraints() {
        chatInput.translatesAutoresizingMaskIntoConstraints = false
        tableView.translatesAutoresizingMaskIntoConstraints = false
        self.view.addConstraints(self.chatInputConstraints())
        self.view.addConstraints(self.tableViewConstraints())
    }
    
    fileprivate func chatInputConstraints() -> [NSLayoutConstraint] {
        self.bottomChatInputConstraint = NSLayoutConstraint(item: chatInput, attribute: .bottom, relatedBy: .equal, toItem: self.bottomLayoutGuide, attribute: .top, multiplier: 1.0, constant: 0)
        let leftConstraint = NSLayoutConstraint(item: chatInput, attribute: .left, relatedBy: .equal, toItem: self.view, attribute: .left, multiplier: 1.0, constant: 0.0)
        let rightConstraint = NSLayoutConstraint(item: chatInput, attribute: .right, relatedBy: .equal, toItem: self.view, attribute: .right, multiplier: 1.0, constant: 0.0)
        return [leftConstraint, self.bottomChatInputConstraint, rightConstraint]
    }
    
    fileprivate func tableViewConstraints() -> [NSLayoutConstraint] {
        let leftConstraint = NSLayoutConstraint(item: tableView, attribute: .left, relatedBy: .equal, toItem: self.view, attribute: .left, multiplier: 1.0, constant: 0.0)
        let rightConstraint = NSLayoutConstraint(item: tableView, attribute: .right, relatedBy: .equal, toItem: self.view, attribute: .right, multiplier: 1.0, constant: 0.0)
        let topConstraint = NSLayoutConstraint(item: tableView, attribute: .top, relatedBy: .equal, toItem: self.view, attribute: .top, multiplier: 1.0, constant: 0.0)
        let bottomConstraint = NSLayoutConstraint(item: tableView, attribute: .bottom, relatedBy: .equal, toItem: chatInput, attribute: .top, multiplier: 1.0, constant: 0)
        return [rightConstraint, leftConstraint, topConstraint, bottomConstraint]//, rightConstraint, bottomConstraint]
    }
    
    // MARK: Keyboard Notifications
    
    fileprivate func listenForKeyboardChanges() {
        let defaultCenter = NotificationCenter.default
        defaultCenter.addObserver(self, selector: #selector(ChatController.keyboardWillChangeFrame(_:)), name: NSNotification.Name.UIKeyboardWillChangeFrame, object: nil)
    }
    
    fileprivate func unregisterKeyboardObservers() {
        NotificationCenter.default.removeObserver(self)
    }
    
    @objc func keyboardWillChangeFrame(_ note: Notification) {
        let keyboardAnimationDetail = (note as NSNotification).userInfo!
        let duration = keyboardAnimationDetail[UIKeyboardAnimationDurationUserInfoKey] as! TimeInterval
        var keyboardFrame = (keyboardAnimationDetail[UIKeyboardFrameEndUserInfoKey] as! NSValue).cgRectValue
        if let window = self.view.window {
            keyboardFrame = window.convert(keyboardFrame, to: self.view)
        }
        let animationCurve = keyboardAnimationDetail[UIKeyboardAnimationCurveUserInfoKey] as! UInt
        
        self.tableView.isScrollEnabled = false
        self.tableView.decelerationRate = UIScrollViewDecelerationRateFast
        self.view.layoutIfNeeded()
        var chatInputOffset = -((self.view.bounds.height - self.bottomLayoutGuide.length) - keyboardFrame.minY)
        if chatInputOffset > 0 {
            chatInputOffset = 0
        }
        self.bottomChatInputConstraint.constant = chatInputOffset
        UIView.animate(withDuration: duration, delay: 0.0, options: UIViewAnimationOptions(rawValue: animationCurve), animations: { () -> Void in
            self.view.layoutIfNeeded()
            self.scrollToBottom()
        }, completion: {(finished) -> () in
            self.tableView.isScrollEnabled = true
            self.tableView.decelerationRate = UIScrollViewDecelerationRateNormal
        })
    }
    
    // MARK: Rotation
    override func viewWillTransition(to size: CGSize, with coordinator: UIViewControllerTransitionCoordinator) {
        coordinator.animate(alongsideTransition: { (_) in
            self.tableView.reloadData()
        }) { (_) in
            UIView.animate(withDuration: 0.25, delay: 0.0, options: UIViewAnimationOptions.curveEaseOut, animations: { () -> Void in
                self.scrollToBottom()
            }, completion: nil)
        }
        
    }
    
    // MARK: Scrolling
    
    fileprivate func scrollToBottom() {
        if messages.count > 0 {
            var lastItemIdx = self.tableView.numberOfRows(inSection: Constants.MessagesSection) - 1
            if lastItemIdx < 0 {
                lastItemIdx = 0
            }
            let lastIndexPath = IndexPath(row: lastItemIdx, section: Constants.MessagesSection)
            self.tableView.scrollToRow(at: lastIndexPath, at: .bottom, animated: false)
        }
    }
    
    // MARK: New messages
    
    func addNewMessage(_ message: ChatMessage) {
        messages += [message]
        tableView.reloadData()
        self.scrollToBottom()
        self.delegate?.chatController?(self, didAddNewMessage: message)
    }
    
    
    // MARK: SwiftChatInputDelegate
    
    func chatInputDidResize(_ chatInput: ChatInput) {
        self.scrollToBottom()
    }
    
    func chatInput(_ chatInput: ChatInput, didSendMessage message: String) {
        let newMessage = ChatMessage(content: message, sentBy: .User)
        var shouldSendMessage = true
        if let value = self.delegate?.shouldChatController?(self, addMessage: newMessage) {
            shouldSendMessage = value
        }
        
        if shouldSendMessage {
            self.addNewMessage(newMessage)
        }
    }
    
    // MARK: UITableViewDelegate
    
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        let padding: CGFloat = 10.0
        sizingCell.bounds.size.width = self.view.bounds.width
        let height = self.sizingCell.setupWithMessage(messages[(indexPath as NSIndexPath).row]).height + padding;
        return height
    }
    
    func scrollViewDidScroll(_ scrollView: UIScrollView) {
        if scrollView.isDragging {
            self.chatInput.textView.resignFirstResponder()
        }
    }
    
    // MARK: UITableViewDataSource
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1;
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.messages.count;
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "identifier", for: indexPath) as! ChatMessageCell
        let message = self.messages[(indexPath as NSIndexPath).row]
        cell.opponentImageView.image = message.sentBy == .Opponent ? self.opponentImage : nil
        cell.userImageView.image = message.sentBy == .User ? self.userImage : nil
        cell.setupWithMessage(message)
        return cell;
    }
    
}

// MARK: Chat Input

protocol ChatInputDelegate : class {
    func chatInputDidResize(_ chatInput: ChatInput)
    func chatInput(_ chatInput: ChatInput, didSendMessage message: String)
}

class ChatInput : UIView, StretchyTextViewDelegate {
    
    // MARK: Styling
    
    struct Appearance {
        static var includeBlur = true
        static var tintColor = UIColor(red: 0.0, green: 120 / 255.0, blue: 255 / 255.0, alpha: 1.0)
        static var backgroundColor = UIColor.white
        static var textViewFont = UIFont.systemFont(ofSize: 17.0)
        static var textViewTextColor = UIColor.darkText
        static var textViewBackgroundColor = UIColor.white
    }
    
    /*
     These methods are included for ObjC compatibility.  If using Swift, you can set the Appearance variables directly.
     */
    
    class func setAppearanceIncludeBlur(_ includeBlur: Bool) {
        Appearance.includeBlur = includeBlur
    }
    
    class func setAppearanceTintColor(_ color: UIColor) {
        Appearance.tintColor = color
    }
    
    class func setAppearanceBackgroundColor(_ color: UIColor) {
        Appearance.backgroundColor = color
    }
    
    class func setAppearanceTextViewFont(_ textViewFont: UIFont) {
        Appearance.textViewFont = textViewFont
    }
    
    class func setAppearanceTextViewTextColor(_ textColor: UIColor) {
        Appearance.textViewTextColor = textColor
    }
    
    class func setAppearanceTextViewBackgroundColor(_ color: UIColor) {
        Appearance.textViewBackgroundColor = color
    }
    
    // MARK: Public Properties
    
    var textViewInsets = UIEdgeInsets(top: 5, left: 5, bottom: 5, right: 5)
    weak var delegate: ChatInputDelegate?
    
    // MARK: Private Properties
    
    fileprivate let textView = StretchyTextView(frame: CGRect.zero, textContainer: nil)
    fileprivate let sendButton = UIButton(type: .system)
    fileprivate let blurredBackgroundView: UIToolbar = UIToolbar()
    fileprivate var heightConstraint: NSLayoutConstraint!
    fileprivate var sendButtonHeightConstraint: NSLayoutConstraint!
    
    // MARK: Initialization
    
    override init(frame: CGRect = CGRect.zero) {
        super.init(frame: frame)
        self.setup()
        self.stylize()
    }
    
    required init(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    // MARK: Setup
    
    func setup() {
        self.translatesAutoresizingMaskIntoConstraints = false
        self.setupSendButton()
        self.setupSendButtonConstraints()
        self.setupTextView()
        self.setupTextViewConstraints()
        self.setupBlurredBackgroundView()
        self.setupBlurredBackgroundViewConstraints()
    }
    
    func setupTextView() {
        textView.bounds = UIEdgeInsetsInsetRect(self.bounds, self.textViewInsets)
        textView.stretchyTextViewDelegate = self
        textView.center = CGPoint(x: self.bounds.midX, y: self.bounds.midY)
        self.styleTextView()
        self.addSubview(textView)
    }
    
    func styleTextView() {
        textView.layer.rasterizationScale = UIScreen.main.scale
        textView.layer.shouldRasterize = true
        textView.layer.cornerRadius = 5.0
        textView.layer.borderWidth = 1.0
        textView.layer.borderColor = UIColor(white: 0.0, alpha: 0.2).cgColor
    }
    
    func setupSendButton() {
        self.sendButton.isEnabled = false
        self.sendButton.setTitle("Send", for: UIControlState())
        self.sendButton.addTarget(self, action: #selector(ChatInput.sendButtonPressed(_:)), for: .touchUpInside)
        self.sendButton.bounds = CGRect(x: 0, y: 0, width: 40, height: 1)
        self.addSubview(sendButton)
    }
    
    func setupSendButtonConstraints() {
        self.sendButton.translatesAutoresizingMaskIntoConstraints = false
        self.sendButton.removeConstraints(self.sendButton.constraints)
        
        // TODO: Fix so that button height doesn't change on first newLine
        let rightConstraint = NSLayoutConstraint(item: self, attribute: .right, relatedBy: .equal, toItem: self.sendButton, attribute: .right, multiplier: 1.0, constant: textViewInsets.right)
        let bottomConstraint = NSLayoutConstraint(item: self, attribute: .bottom, relatedBy: .equal, toItem: self.sendButton, attribute: .bottom, multiplier: 1.0, constant: textViewInsets.bottom)
        let widthConstraint = NSLayoutConstraint(item: self.sendButton, attribute: .width, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: 40)
        sendButtonHeightConstraint = NSLayoutConstraint(item: self.sendButton, attribute: .height, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: 30)
        self.addConstraints([sendButtonHeightConstraint, widthConstraint, rightConstraint, bottomConstraint])
    }
    
    func setupTextViewConstraints() {
        self.textView.translatesAutoresizingMaskIntoConstraints = false
        let topConstraint = NSLayoutConstraint(item: self, attribute: .top, relatedBy: .equal, toItem: self.textView, attribute: .top, multiplier: 1.0, constant: -textViewInsets.top)
        let leftConstraint = NSLayoutConstraint(item: self, attribute: .left, relatedBy: .equal, toItem: self.textView, attribute: .left, multiplier: 1, constant: -textViewInsets.left)
        let bottomConstraint = NSLayoutConstraint(item: self, attribute: .bottom, relatedBy: .equal, toItem: self.textView, attribute: .bottom, multiplier: 1, constant: textViewInsets.bottom)
        let rightConstraint = NSLayoutConstraint(item: self.textView, attribute: .right, relatedBy: .equal, toItem: self.sendButton, attribute: .left, multiplier: 1, constant: -textViewInsets.right)
        heightConstraint = NSLayoutConstraint(item: self, attribute: .height, relatedBy: .equal, toItem: nil, attribute: .height, multiplier: 1.00, constant: 40)
        self.addConstraints([topConstraint, leftConstraint, bottomConstraint, rightConstraint, heightConstraint])
    }
    
    func setupBlurredBackgroundView() {
        self.addSubview(self.blurredBackgroundView)
        self.sendSubview(toBack: self.blurredBackgroundView)
    }
    
    func setupBlurredBackgroundViewConstraints() {
        self.blurredBackgroundView.translatesAutoresizingMaskIntoConstraints = false
        let topConstraint = NSLayoutConstraint(item: self, attribute: .top, relatedBy: .equal, toItem: self.blurredBackgroundView, attribute: .top, multiplier: 1.0, constant: 0)
        let leftConstraint = NSLayoutConstraint(item: self, attribute: .left, relatedBy: .equal, toItem: self.blurredBackgroundView, attribute: .left, multiplier: 1.0, constant: 0)
        let bottomConstraint = NSLayoutConstraint(item: self, attribute: .bottom, relatedBy: .equal, toItem: self.blurredBackgroundView, attribute: .bottom, multiplier: 1.0, constant: 0)
        let rightConstraint = NSLayoutConstraint(item: self, attribute: .right, relatedBy: .equal, toItem: self.blurredBackgroundView, attribute: .right, multiplier: 1.0, constant: 0)
        self.addConstraints([topConstraint, leftConstraint, bottomConstraint, rightConstraint])
    }
    
    // MARK: Styling
    
    func stylize() {
        self.textView.backgroundColor = Appearance.textViewBackgroundColor
        self.sendButton.tintColor = Appearance.tintColor
        self.textView.tintColor = Appearance.tintColor
        self.textView.font = Appearance.textViewFont
        self.textView.textColor = Appearance.textViewTextColor
        self.blurredBackgroundView.isHidden = !Appearance.includeBlur
        self.backgroundColor = Appearance.backgroundColor
    }
    
    // MARK: StretchyTextViewDelegate
    
    func stretchyTextViewDidChangeSize(_ textView: StretchyTextView) {
        let textViewHeight = textView.bounds.height
        if textView.text.characters.count == 0 {
            self.sendButtonHeightConstraint.constant = textViewHeight
        }
        let targetConstant = textViewHeight + textViewInsets.top + textViewInsets.bottom
        self.heightConstraint.constant = targetConstant
        self.delegate?.chatInputDidResize(self)
    }
    
    func stretchyTextView(_ textView: StretchyTextView, validityDidChange isValid: Bool) {
        self.sendButton.isEnabled = isValid
    }
    
    // MARK: Button Presses
    
    @objc func sendButtonPressed(_ sender: UIButton) {
        if self.textView.text.characters.count > 0 {
            self.delegate?.chatInput(self, didSendMessage: self.textView.text)
            self.textView.text = ""
        }
    }
}

// MARK: Text View

@objc protocol StretchyTextViewDelegate {
    func stretchyTextViewDidChangeSize(_ chatInput: StretchyTextView)
    @objc optional func stretchyTextView(_ textView: StretchyTextView, validityDidChange isValid: Bool)
}

class StretchyTextView : UITextView, UITextViewDelegate {
    
    // MARK: Delegate
    
    weak var stretchyTextViewDelegate: StretchyTextViewDelegate?
    
    // MARK: Public Properties
    
    var maxHeightPortrait: CGFloat = 160
    var maxHeightLandScape: CGFloat = 60
    var maxHeight: CGFloat {
        get {
            return UIInterfaceOrientationIsPortrait(UIApplication.shared.statusBarOrientation) ? maxHeightPortrait : maxHeightLandScape
        }
    }
    // MARK: Private Properties
    
    fileprivate var maxSize: CGSize {
        get {
            return CGSize(width: self.bounds.width, height: self.maxHeightPortrait)
        }
    }
    
    fileprivate var isValid: Bool = false {
        didSet {
            if isValid != oldValue {
                stretchyTextViewDelegate?.stretchyTextView?(self, validityDidChange: isValid)
            }
        }
    }
    
    fileprivate let sizingTextView = UITextView()
    
    // MARK: Property Overrides
    
    override var contentSize: CGSize {
        didSet {
            resize()
        }
    }
    
    override var font: UIFont! {
        didSet {
            sizingTextView.font = font
        }
    }
    
    override var textContainerInset: UIEdgeInsets {
        didSet {
            sizingTextView.textContainerInset = textContainerInset
        }
    }
    
    // MARK: Initializers
    
    override init(frame: CGRect = CGRect.zero, textContainer: NSTextContainer? = nil) {
        super.init(frame: frame, textContainer: textContainer);
        setup()
    }
    
    required init(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    // MARK: Setup
    
    func setup() {
        font = UIFont.systemFont(ofSize: 17.0)
        textContainerInset = UIEdgeInsets(top: 2, left: 2, bottom: 2, right: 2)
        delegate = self
    }
    
    // MARK: Sizing
    
    func resize() {
        bounds.size.height = self.targetHeight()
        stretchyTextViewDelegate?.stretchyTextViewDidChangeSize(self)
    }
    
    func targetHeight() -> CGFloat {
        
        /*
         There is an issue when calling `sizeThatFits` on self that results in really weird drawing issues with aligning line breaks ("\n").  For that reason, we have a textView whose job it is to size the textView. It's excess, but apparently necessary.  If there's been an update to the system and this is no longer necessary, or if you find a better solution. Please remove it and submit a pull request as I'd rather not have it.
         */
        
        sizingTextView.text = self.text
        let targetSize = sizingTextView.sizeThatFits(maxSize)
        let targetHeight = targetSize.height
        let maxHeight = self.maxHeight
        return targetHeight < maxHeight ? targetHeight : maxHeight
    }
    
    // MARK: Alignment
    
    func align() {
        guard let end = self.selectedTextRange?.end, let caretRect: CGRect = self.caretRect(for: end) else { return }
        
        let topOfLine = caretRect.minY
        let bottomOfLine = caretRect.maxY
        
        let contentOffsetTop = self.contentOffset.y
        let bottomOfVisibleTextArea = contentOffsetTop + self.bounds.height
        
        /*
         If the caretHeight and the inset padding is greater than the total bounds then we are on the first line and aligning will cause bouncing.
         */
        
        let caretHeightPlusInsets = caretRect.height + self.textContainerInset.top + self.textContainerInset.bottom
        if caretHeightPlusInsets < self.bounds.height {
            var overflow: CGFloat = 0.0
            if topOfLine < contentOffsetTop + self.textContainerInset.top {
                overflow = topOfLine - contentOffsetTop - self.textContainerInset.top
            } else if bottomOfLine > bottomOfVisibleTextArea - self.textContainerInset.bottom {
                overflow = (bottomOfLine - bottomOfVisibleTextArea) + self.textContainerInset.bottom
            }
            self.contentOffset.y += overflow
        }
    }
    
    // MARK: UITextViewDelegate
    
    func textViewDidChangeSelection(_ textView: UITextView) {
        self.align()
    }
    
    func textViewDidChange(_ textView: UITextView) {
        // TODO: Possibly filter spaces and newlines
        self.isValid = textView.text.characters.count > 0
    }
}
