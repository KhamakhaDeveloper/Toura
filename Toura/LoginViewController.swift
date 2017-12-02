//
//  LoginViewController.swift
//  Toura
//
//  Created by Carpenter, Deepak (US - Bengaluru) on 02/12/17.
//  Copyright © 2017 TechMusketeers. All rights reserved.
//

import UIKit

import UIKit

class LoginViewController: UIViewController {
    enum CommonString : String {
        case StoryboardId = "Main"
        case controllerId = "MainView"
    }
   
    @IBOutlet var logoVerticalConstraint: NSLayoutConstraint!
    @IBOutlet var userNameTextField: UITextField!
    override func viewDidLoad() {
        super.viewDidLoad()
    
        // Do any additional setup after loading the view.
        self.setupNotification()
        userNameTextField.delegate = self
    }
    
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(true)
        UIView.animate(withDuration: 1.0, animations: {
            self.logoVerticalConstraint.constant = -150
            self.view.layoutSubviews()
        })
        self.transparentNavigationBar()
        UIApplication.shared.statusBarStyle = .lightContent
    }
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
     // In a storyboard-based application, you will often want to do a little preparation before navigation
     override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
     // Get the new view controller using segue.destinationViewController.
     // Pass the selected object to the new view controller.
      
     }
 
     @IBAction func loginButtonTapped(_ sender: Any) {
       performSegue(withIdentifier: LoginViewController.CommonString.controllerId.rawValue, sender: nil)
    }
    
}
extension LoginViewController : UITextFieldDelegate {
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        userNameTextField.resignFirstResponder()
        return true
    }
}
extension LoginViewController {
    func setupNotification(){
        NotificationCenter.default.addObserver(self,
                                               selector: #selector(LoginViewController.keyboardWillShow(notification:)),
                                               name: NSNotification.Name.UIKeyboardWillShow, object: nil)
        NotificationCenter.default.addObserver(self,
                                               selector: #selector(LoginViewController.keyboardWillHide(notification:)),
                                               name: NSNotification.Name.UIKeyboardWillHide, object: nil)
    }
    @objc func keyboardWillShow(notification: NSNotification) {
        if ((notification.userInfo?[UIKeyboardFrameBeginUserInfoKey] as? NSValue)?.cgRectValue) != nil {
            UIView.animate(withDuration: 1.5, animations: {
                self.logoVerticalConstraint.constant = self.logoVerticalConstraint.constant - 80
                self.view.layoutIfNeeded()
            })
        }
    }
    @objc func keyboardWillHide(notification: NSNotification) {
        if ((notification.userInfo?[UIKeyboardFrameBeginUserInfoKey] as? NSValue)?.cgRectValue) != nil {
            UIView.animate(withDuration: 1.5, animations: {
                self.logoVerticalConstraint.constant = self.logoVerticalConstraint.constant + 80
                self.view.layoutIfNeeded()
            })
        }
    }
}
