import Foundation

let placesJson = """
{
   "candidates" : [
      {
         "geometry" : {
            "location" : {
               "lat" : 48.470247,
               "lng" : 35.036206
            }
         },
         "name" : "Coffee Life"
      },
      {
         "geometry" : {
            "location" : {
               "lat" : 48.469434,
               "lng" : 35.038985
            }
         },
         "name" : "Have Coffee"
      },
      {
         "geometry" : {
            "location" : {
               "lat" : 48.466561,
               "lng" : 35.045186
            }
         },
         "name" : "AROMA KAVA"
      },
      {
         "geometry" : {
            "location" : {
               "lat" : 48.463783,
               "lng" : 35.042595
            }
         },
         "name" : "Mr. Coffee"
      },
      {
         "geometry" : {
            "location" : {
               "lat" : 48.463516,
               "lng" : 35.048889
            }
         },
         "name" : "DoubleDecker"
      },
      {
         "geometry" : {
            "location" : {
               "lat" : 48.425694,
               "lng" : 35.025487
            }
         },
         "name" : "Mocco bar"
      },
      {
         "geometry" : {
            "location" : {
               "lat" : 48.451214,
               "lng" : 35.057789
            }
         },
         "name" : "Confetti"
      },
      {
         "geometry" : {
            "location" : {
               "lat" : 48.460239,
               "lng" : 35.069301
            }
         },
         "name" : "One dollar bar"
      },
      {
         "geometry" : {
            "location" : {
               "lat" : 48.459414,
               "lng" : 35.064731
            }
         },
         "name" : "Heisenberg Coffee Lab"
      },
      {
         "geometry" : {
            "location" : {
               "lat" : 48.423311,
               "lng" : 35.058121
            }
         },
         "name" : "Sopranos"
      }]
}
"""

struct Location: Codable {
    let lat: Double
    let lng: Double
}

struct Geometry: Codable {
    let location: Location
}

struct Candidate: Codable {
    let geometry: Geometry
    let name: String
}

struct Places: Codable {
    let candidates: [Candidate]?
}

func parsePlacesJson(data: String) -> Places? {
    do {
        let jsonData = data.data(using: .utf8)!
        let places: Places = try! JSONDecoder().decode(Places.self, from: jsonData)
        // print(places)

        return places
    }
    catch {
        print("Error until decoding json file");
        exit(1);
    }
}

class CoolPlacesNearMe {
    var base_location = Location(lat: 48.471207, lng: 35.038810)

    let all_places: Places?
    let radius: Double

    init(places_json: String, rhs_radius: Double) {
        all_places = parsePlacesJson(data: places_json)
        radius = rhs_radius;
    }

    func toRadian(value: Double) -> Double {
        var PI = 3.14
        return value * PI / 180.0  
    }
    
    func calcDistance(rhs_location: Location) -> Double {
         var EARTH_RADIUS = 6378.1

        let f1 = toRadian(value: base_location.lat)
        let f2 = toRadian(value: rhs_location.lat)
        let delta_f = abs(f1 - f2);

        let alpha1 = toRadian(value: base_location.lng)
        let alpha2 = toRadian(value: rhs_location.lng)
        let delta_alpha = abs(alpha1 - alpha2)

        let a = sin(delta_f / 2) * sin(delta_f / 2) + 
                cos(f1) * cos(f1) * 
                sin(delta_alpha / 2) * sin(delta_alpha / 2)

        let c = 2 * atan2(sqrt(a), sqrt(1 - a))

        return EARTH_RADIUS * c
    }

    func findNearestPlaces() -> Places? {
        if let all_places_candidates = all_places?.candidates {
            let nearestPlaces = all_places_candidates.filter { 
                candidate in
                let distance = calcDistance(rhs_location: candidate.geometry.location)
                return distance <= radius
            }

            if nearestPlaces.isEmpty {
                return nil
            }

            return Places(candidates: nearestPlaces)
        } 
        else {
            return nil
        }
    }

    func printNearestPlacesInfo() {
        if let nearest_places = findNearestPlaces()?.candidates {
            for place in nearest_places {
                print("Place name: \(place.name)")
                print("Coordinates: (\(place.geometry.location.lat), \(place.geometry.location.lng))")
                print()
            }
        } 
        else {
            print("There is no places so close")
        }
    }

}

let example = CoolPlacesNearMe(places_json: placesJson, rhs_radius: 0.8)
example.printNearestPlacesInfo()

