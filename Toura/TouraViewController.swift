//
//  TouraViewController.swift
//  Toura
//
//  Created by Carpenter, Deepak (US - Bengaluru) on 02/12/17.
//  Copyright © 2017 TechMusketeers. All rights reserved.
//

import Foundation
import UIKit
import AVFoundation
import ApiAI
class TouraViewController: ChatController {
    
    let defaultMessage =
    "Hi There, Welcome To The land of deserts, I am Toura, I am here to help you, To Start tell me where you want to go to ?"//"Hi Deepak. This is Toura. How may i help you ?. Ask me anything about Rajasthan Tourism"
    let speechSynthesizer = AVSpeechSynthesizer()
    
    func speechAndText(text: String) {
        let speechUtterance = AVSpeechUtterance(string: text)
        speechUtterance.voice  = AVSpeechSynthesisVoice(language: "en-AU")
        speechUtterance.accessibilityContainerType = .landmark
        speechUtterance.preUtteranceDelay = 1.0
        speechUtterance.postUtteranceDelay = 1.0
        speechSynthesizer.speak(speechUtterance)
        UIView.animate(withDuration: 1.0, delay: 0.0, options: .allowAnimatedContent, animations: {
        }, completion: nil)
    }
    
    func setUpAPIAI(){
        let configuration = AIDefaultConfiguration()
        configuration.clientAccessToken = "b333d41eab8d4683bf564cc6b96171ec"
        let apiai = ApiAI.shared()
        apiai?.configuration = configuration
    }
    override func viewDidLoad() {

        super.viewDidLoad()
        // Do any additional setup after loading the view.
        self.setUpAPIAI()
        self.delegate = self
        setupChatController()
        self.title = "Toura Chat"
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    //MARK: - Setup ChatController
    func setupChatController(){
        self.opponentImage = UIImage(named : "User")
        //self.userImage = UIImage(named : "User")
        let helloWorld = ChatMessage(content: defaultMessage, sentBy: .Opponent, timeStamp: Date.timeIntervalSinceReferenceDate)
        speechAndText(text: defaultMessage)
        self.messages = [helloWorld]
    }
    
    //MARK: - Setup ChatController
    func setupRecievedMessage(chatMessage : String){
        let cm = ChatMessage(content: chatMessage, sentBy: .Opponent, timeStamp: Date.timeIntervalSinceReferenceDate)
        speechAndText(text: chatMessage)
        self.messages.append(cm)
    }
    
    //MARK: - Setup ImageMessage
    func setupRecievedMessage(chatMessage : String, image : UIImage){
        let cm = ChatMessage(content: chatMessage, sentBy: .Opponent, image: image)
        speechAndText(text: chatMessage)
        self.messages.append(cm)
    }
    
    
    //MARK: - Setup ChatController
    func chatController(_ chatController: ChatController, didAddNewMessage message: ChatMessage) {
        print("Did Add Message: \(message.content)")
        print("All Messages \(message.sentBy)")
        
    }
    
    func shouldChatController(_ chatController: ChatController, addMessage message: ChatMessage) -> Bool {
        ChatMessage.SentByUserString()
        sendMessageToAI(message: message.content)
        //message.sentByString = arc4random_uniform(2) == 0 ? ChatMessage.SentByOpponentString() : ChatMessage.SentByUserString()
        return true
    }
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
    func popUpPicture(urlString : String)-> UIImage{
        var iconImage = UIImage()
        let iconImageView = UIImageView()
        if let url = URL(string: urlString){
          iconImage = iconImageView.downloadedFrom(url: url)
        }
        return iconImage
    }
    
    func sendMessageToAI(message : String){
        let request = ApiAI.shared().textRequest()
        request?.query = message
        request?.setMappedCompletionBlockSuccess({ (request, response) in
            let response = response as! AIResponse
            if let textResponse = response.result.fulfillment.speech {
                DispatchQueue.main.async {
                    self.urlDetector(text: textResponse) ?self.setupRecievedMessage(chatMessage: textResponse, image: self.popUpPicture(urlString: textResponse)) : self.setupRecievedMessage(chatMessage: textResponse)
                    self.delegate?.reloadMeassages(isReload: true)
                }
                print(response.result.fulfillment.messages)
                
            }
        }, failure: { (request, error) in
            print("error \(error!)")
        })
        
        ApiAI.shared().enqueue(request)
    }
}

