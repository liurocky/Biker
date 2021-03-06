/*
    Biker wants to be a routing software, intended to be useful for planning bike tours.
    Copyright (C) 2011  Lena Brueder

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/ 

#ifndef GPSROUTE_HPP
#define GPSROUTE_HPP

#include "src/DataPrimitives/DataPrimitiveDefines.hpp"
#include "src/DataPrimitives/gpsposition.hpp"
#include <QList>

class GPSRoute
{
public:
    /**
     * Diese Funktion gibt die Länge der Route über die Wegpunkte an.
     * Es werden alle Teilstücke des Streckenzugs über die einzelnen Wegpunkte
     * aufsummiert, Einheit ist Meter.
     */
    double calcLength() const;

    /**
     * Diese Funktion gibt die Länge der Reststrecke ab einem gewissen Wegpunktindex an.
     */
    double calcLengthStartingAtID(int id) const;

    /**
     * Gibt den Zielpunkt zurück.
     */
    GPSPosition getDestination() const;
    /**
     * Setzt den Zielpunkt. Dieser muss nicht
     * Teil der Route sein, damit man auch ohne
     * Route - nur mit Start- und Endpunkt - arbeiten
     * kann.
     */
    void setDestination(GPSPosition dest);

    /**
     * Gibt den Startpunkt zurück.
     */
    GPSPosition getStartingPoint() const;
    /**
     * Setzt den Startpunkt. Dieser muss nicht
     * Teil der Route sein, damit man auch ohne
     * Route - nur mit Start- und Endpunkt - arbeiten
     * kann.
     */
    void setStartingPoint(GPSPosition start);

    /**
     * Fügt einen Wegpunkt zur Route hinzu, am Ende der
     * Route.
     */
    void addWaypoint(GPSPosition p);

    void addRoute(GPSRoute route);

    /**
     * Fügt einen Wegpunkt am Anfang der Route hinzu.
     * @param p
     */
    void addWaypointInFront(GPSPosition p);
    /**
     * Sucht den Wegpunkt heraus, der zu einem geg. Punkt
     * die größte geographische Nähe aufweist. Dies muss nicht
     * unbedingt der Wegpunkt sein, den man ansteuern möchte:
     * Es kann ja sein, dass man ihn bereits besucht hat.
     */
    GPSPosition getClosestWaypoint(GPSPosition p) const;
    int getClosestWaypointID(GPSPosition p) const;

    /**
     * Gibt den i-ten Wegpunkt zurück.
     */
    GPSPosition getWaypoint(int i) const;

    /**
     * Gibt die Anzahl Punkt zurück, die in der Route gespeichert sind.
     * Da eine Route immer den Start- und Endpunkt enthält, ist die Größe immer
     * >= 2.
     */
    int size() const;

    /**
     * Zeigt an, ob in der Route Werte gespeichert sind, oder nicht.
     */
    bool isEmpty() const;
    /**
     * Leert die Route komplett.
     */
    void clear();

    /**
     * Diese Funktion berechnet die Koordinaten eines Punktes in einer gewissen
     * Entfernung entlang der Route. pStart ist dabei der Punkt, von dem aus
     * die Entfernungsangabe passen soll, nextWaypointID ist die Nummer des zuerst
     * anzusteuernden Wegpunktes.
     */
    GPSPosition calcPositionInDistance(GPSPosition pStart, float maxDistance, int nextWaypointID) const;

    /**
     * Diese Funktion importiert Daten aus einer GPX-Datei.
     */
    static GPSRoute importGPX(QString gpxFilename);

    /**
     * Diese Funktion exportiert die Route in das GPX-Format, sodass sie
     * von anderen Applikationen benutzt werden kann.
     */
    static void exportGPX(QString gpxFilename, GPSRoute r);

    /**
     * Dreht eine Route um, damit man sie in die entgegengesetzte Richtung befahren kann
     * und trotzdem alle Anzeigen stimmen.
     */
    void reverse();

    GPSRoute();
    GPSRoute(const GPSRoute& r);
private:
    QList<GPSPosition> waypointList;

    int actWaypoint;	//der aktuell nächste Wegpunkt, der angesteuert wird.
};

#endif // GPSROUTE_HPP
