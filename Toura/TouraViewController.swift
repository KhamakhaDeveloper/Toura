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
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        self.delegate = self
        setupChatController()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    //MARK: - Setup ChatController
    func setupChatController(){
        self.opponentImage = UIImage(named : "User")
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
    
    func sendMessageToAI(message : String){
        let request = ApiAI.shared().textRequest()
        request?.query = message
        
        request?.setMappedCompletionBlockSuccess({ (request, response) in
            let response = response as! AIResponse
            if let textResponse = response.result.fulfillment.speech {
                DispatchQueue.main.async {
                    self.setupRecievedMessage(chatMessage: textResponse)
                    self.delegate?.reloadMeassages(isReload: true)
                }
                print(response.result.fulfillment.messages)
                
            }
        }, failure: { (request, error) in
            print(error!)
        })
        
        ApiAI.shared().enqueue(request)
    }
}
